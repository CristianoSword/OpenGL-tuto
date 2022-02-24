#include <iostream>
#include <memory>
#include "Window.h"
#include "MyScene.h"
//#define GLEW_STATIC

int main(int argc, char** argv)
{

	Window w(450, 300, "Intruducao OpenGL - Design Code Play Repeat!");
	//std::cout << "Hello OpenGL" << std::endl;
	w.setScene(std::unique_ptr<Scene>(new MyScene()));

	while (!w.shouldClose())
	{
		w.update();
	}

	return 0;
}

