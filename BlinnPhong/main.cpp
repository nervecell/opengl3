//
//  main.cpp
//  BlinnPhong
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "BlinnPhong.h"

int main(void)
{
	BlinnPhong app;
	app.initGLApp("Blinn Phong", 1280, 720);
	app.init();
	app.run();
	return 0;
}
