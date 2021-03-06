#include <cmath>
#include "Colors.h"
#include "image/GLImage.h"


Colors::Colors():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
m_lightPos(1.2f, 1.0f, 2.0f)
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void Colors::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    
    m_cubeVAO.gen();

    m_VBO.gen();
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_cubeVAO.bind();
    //position attribute
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();
    
    m_ligthVAO.gen();
    m_ligthVAO.bind();
    
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

}

void Colors::initProgram()
{
    this->createPrograme("Shaders/Colors.vert", "Shaders/Colors.frag", m_lightingShader);
    this->createPrograme("Shaders/Lamp.vert", "Shaders/Lamp.frag", m_lampShader);
}

void Colors::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //light
    m_lightingShader.use();
    m_lightingShader.getUniform("objectColor")->value3f(1.0f, 0.5f, 0.31f);
    m_lightingShader.getUniform("lightColor")->value3f(1.0f, 1.0f, 1.0f);
    
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_lightingShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lightingShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    glm::mat4 model;
    m_lightingShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    m_cubeVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //lamp
    m_lampShader.use();
    m_lampShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lampShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    model = glm::mat4();
    model = glm::translate(model, m_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cub
    m_lampShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    m_ligthVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Colors::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void Colors::onTouchMove(float x, float y)
{
    if (m_firstMouse)
    {
        m_lastX = x;
        m_lastY = y;
        m_firstMouse = false;
    }
    
    float xoffset = x - m_lastX;
    float yoffset = m_lastY - y;
    
    m_lastX = x;
    m_lastY = y;
    
    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void Colors::onTouchEnd(float x, float y)
{
    
}

void Colors::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void Colors::onKeyPress(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_W)
    {
        m_camera.ProcessKeyboard(FORWARD, m_deltaTime);
    }
    else if(key == GLFW_KEY_S)
    {
        m_camera.ProcessKeyboard(BACKWARD, m_deltaTime);
    }
    else if(key == GLFW_KEY_A)
    {
        m_camera.ProcessKeyboard(LEFT, m_deltaTime);
    }
    else if(key == GLFW_KEY_D)
    {
        m_camera.ProcessKeyboard(RIGHT, m_deltaTime);
    }
}

