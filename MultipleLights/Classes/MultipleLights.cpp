#include <cmath>
#include "MultipleLights.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"

MultipleLights::MultipleLights():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
m_lightPos(1.2f, 1.0f, 2.0f)
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void MultipleLights::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
    m_cubePositions.push_back(glm::vec3( 0.0f,  0.0f,  0.0f));
    m_cubePositions.push_back(glm::vec3( 2.0f,  5.0f, -15.0f));
    m_cubePositions.push_back(glm::vec3(-1.5f, -2.2f, -2.5f));
    m_cubePositions.push_back(glm::vec3(-3.8f, -2.0f, -12.3f));
    m_cubePositions.push_back(glm::vec3( 2.4f, -0.4f, -3.5f));
    m_cubePositions.push_back(glm::vec3(-1.7f,  3.0f, -7.5f));
    m_cubePositions.push_back(glm::vec3( 1.3f, -2.0f, -2.5f));
    m_cubePositions.push_back(glm::vec3( 1.5f,  2.0f, -2.5f));
    m_cubePositions.push_back(glm::vec3( 1.5f,  0.2f, -1.5f));
    m_cubePositions.push_back(glm::vec3(-1.3f,  1.0f, -1.5f));
    
    m_pointLightPositions.push_back(glm::vec3( 0.7f,  0.2f,  2.0f));
    m_pointLightPositions.push_back(glm::vec3( 2.3f, -3.3f, -4.0f));
    m_pointLightPositions.push_back(glm::vec3(-4.0f,  2.0f, -12.0f));
    m_pointLightPositions.push_back(glm::vec3( 0.0f,  0.0f, -3.0f));
    
    m_cubeVAO.gen();

    m_VBO.gen();
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_cubeVAO.bind();
    //position attribute
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();
    //normal attribute
    m_normalAttr.init(1);
    m_normalAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    m_normalAttr.enableVertexAttribArray();
    //texture attribute
    m_texAttr.init(2);
    m_texAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    m_texAttr.enableVertexAttribArray();
    
    m_ligthVAO.gen();
    m_ligthVAO.bind();
    
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

    m_diffuseMap.initWithImage("container2.png");
    m_specularMap.initWithImage("container2_specular.png");
    
    m_lightingShader.use();
    m_lightingShader.getUniform("material.diffuse")->value1i(0);
    m_lightingShader.getUniform("material.specular")->value1i(1);
}

void MultipleLights::initProgram()
{
    this->createPrograme("Shaders/MultipleLights.vert", "Shaders/MultipleLights.frag", m_lightingShader);
    this->createPrograme("Shaders/Lamp.vert", "Shaders/Lamp.frag", m_lampShader);
}

void MultipleLights::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //light
    m_lightingShader.use();
    m_lightingShader.getUniform("material.shininess")->value1f(32.0f);
    m_lightingShader.getUniform("viewPos")->vector3fv(1, &m_camera.Position[0]);
    //directional light
    m_lightingShader.getUniform("dirLight.direction")->value3f(-0.2f, -1.0f, -0.3f);
    m_lightingShader.getUniform("dirLight.ambient")->value3f(0.05f, 0.05f, 0.05f);
    m_lightingShader.getUniform("dirLight.diffuse")->value3f(0.4f, 0.4f, 0.4f);
    m_lightingShader.getUniform("dirLight.specular")->value3f(0.5f, 0.5f, 0.5f);
    //point light 1
    m_lightingShader.getUniform("pointLights[0].position")->vector3fv(1, glm::value_ptr(m_pointLightPositions[0]));
    m_lightingShader.getUniform("pointLights[0].ambient")->value3f(0.05f, 0.05f, 0.05f);
    m_lightingShader.getUniform("pointLights[0].diffuse")->value3f(0.8f, 0.8f, 0.8f);
    m_lightingShader.getUniform("pointLights[0].specular")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("pointLights[0].constant")->value1f(1.0f);
    m_lightingShader.getUniform("pointLights[0].linear")->value1f(0.09f);
    m_lightingShader.getUniform("pointLights[0].quadratic")->value1f(0.032f);
    //point light 2
    m_lightingShader.getUniform("pointLights[1].position")->vector3fv(1, glm::value_ptr(m_pointLightPositions[1]));
    m_lightingShader.getUniform("pointLights[1].ambient")->value3f(0.05f, 0.05f, 0.05f);
    m_lightingShader.getUniform("pointLights[1].diffuse")->value3f(0.8f, 0.8f, 0.8f);
    m_lightingShader.getUniform("pointLights[1].specular")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("pointLights[1].constant")->value1f(1.0f);
    m_lightingShader.getUniform("pointLights[1].linear")->value1f(0.09f);
    m_lightingShader.getUniform("pointLights[1].quadratic")->value1f(0.032f);
    //point light 3
    m_lightingShader.getUniform("pointLights[2].position")->vector3fv(1, glm::value_ptr(m_pointLightPositions[2]));
    m_lightingShader.getUniform("pointLights[2].ambient")->value3f(0.05f, 0.05f, 0.05f);
    m_lightingShader.getUniform("pointLights[2].diffuse")->value3f(0.8f, 0.8f, 0.8f);
    m_lightingShader.getUniform("pointLights[2].specular")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("pointLights[2].constant")->value1f(1.0f);
    m_lightingShader.getUniform("pointLights[2].linear")->value1f(0.09f);
    m_lightingShader.getUniform("pointLights[2].quadratic")->value1f(0.032f);
    //point light 4
    m_lightingShader.getUniform("pointLights[3].position")->vector3fv(1, glm::value_ptr(m_pointLightPositions[3]));
    m_lightingShader.getUniform("pointLights[3].ambient")->value3f(0.05f, 0.05f, 0.05f);
    m_lightingShader.getUniform("pointLights[3].diffuse")->value3f(0.8f, 0.8f, 0.8f);
    m_lightingShader.getUniform("pointLights[3].specular")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("pointLights[3].constant")->value1f(1.0f);
    m_lightingShader.getUniform("pointLights[3].linear")->value1f(0.09f);
    m_lightingShader.getUniform("pointLights[3].quadratic")->value1f(0.032f);
    //spotLight
    m_lightingShader.getUniform("spotLight.position")->vector3fv(1, &m_camera.Position[0]);
    m_lightingShader.getUniform("spotLight.direction")->vector3fv(1, &m_camera.Front[0]);
    m_lightingShader.getUniform("spotLight.ambient")->value3f(0.0f, 0.0f, 0.0f);
    m_lightingShader.getUniform("spotLight.diffuse")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("spotLight.specular")->value3f(1.0f, 1.0f, 1.0f);
    m_lightingShader.getUniform("spotLight.constant")->value1f(1.0f);
    m_lightingShader.getUniform("spotLight.linear")->value1f(0.09f);
    m_lightingShader.getUniform("spotLight.quadratic")->value1f(0.032f);
    m_lightingShader.getUniform("spotLight.cutOff")->value1f(glm::cos(glm::radians(12.5f)));
    m_lightingShader.getUniform("spotLight.outerCutOff")->value1f(glm::cos(glm::radians(15.0f)));
    
    //light properties
    m_lightingShader.getUniform("light.ambient")->value3f(0.1f, 0.1f, 0.1f);
    m_lightingShader.getUniform("light.diffuse")->value3f(0.8f, 0.8f, 0.8f);
    m_lightingShader.getUniform("light.specular")->value3f(1.0f, 1.0f, 1.0f);
    
    m_lightingShader.getUniform("light.constant")->value1f(1.0f);
    m_lightingShader.getUniform("light.linear")->value1f(0.09f);
    m_lightingShader.getUniform("light.quadratic")->value1f(0.032f);
    
    //material properties

    
    //view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_lightingShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lightingShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    // world transformation
    glm::mat4 model(1);
    m_lightingShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    GLTexture::activeTexture(GL_TEXTURE0);
    m_diffuseMap.bindTexture(GL_TEXTURE_2D);
    
    GLTexture::activeTexture(GL_TEXTURE1);
    m_specularMap.bindTexture(GL_TEXTURE_2D);
    
    //reander the cube
    m_cubeVAO.bind();
    for(int i = 0; i < m_cubePositions.size(); i++)
    {
        glm::mat4 model(1);
        model = glm::translate(model, m_cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_lightingShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    //lamp
    m_lampShader.use();
    m_lampShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lampShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    //we now draw as many light bulbs as we have point lights
    m_ligthVAO.bind();
    for(int i = 0; i < m_pointLightPositions.size(); i++)
    {
        model = glm::mat4();
        model = glm::translate(model, m_pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cub
        m_lampShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
}

void MultipleLights::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void MultipleLights::onTouchMove(float x, float y)
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

void MultipleLights::onTouchEnd(float x, float y)
{
    
}

void MultipleLights::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void MultipleLights::onKeyPress(int key, int scancode, int action, int mods)
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

