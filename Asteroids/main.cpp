//
//  main.cpp
//  Asteroids
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "Asteroids.h"

int main(void)
{
	Asteroids app;
	app.initGLApp("Asteroids", 1280, 720);
	app.init();
	app.run();
	return 0;
}
