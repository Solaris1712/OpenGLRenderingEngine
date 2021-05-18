#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowGen
{
public:
	WindowGen();
	WindowGen(GLint windowWidth,GLint windowHeight);

	int Initialize();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return !glfwWindowShouldClose(Window); }
	bool* getKeys() { return keys; }
	GLfloat getChangeX();
	GLfloat getChangeY();
	void swapBuffers() { glfwSwapBuffers(Window); }




	~WindowGen();

private:

	GLFWwindow* Window;
	GLint WIDTH, HEIGHT;
	GLint bufferWidth, bufferHeight;

	GLfloat lastX, lastY, changeX, changeY;
	bool mouseFirstTimeMoved;

	bool keys[1024];

	static void handleKeys(GLFWwindow* window,int key,int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	void CreateCallbacks();

};

