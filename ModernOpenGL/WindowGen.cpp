#include "WindowGen.h"

WindowGen::WindowGen()
{
	WIDTH = 800;
	HEIGHT = 600;
	changeX = changeY = 0;
	mouseFirstTimeMoved = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

}

WindowGen::WindowGen(GLint windowWidth, GLint windowHeight)
{
	WIDTH = windowWidth;
	HEIGHT = windowHeight;
	changeX = changeY = 0;
	mouseFirstTimeMoved = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	
}

int WindowGen::Initialize()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW - Code-0");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	Window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);
	if (!Window)
	{
		printf("Window Initialization failed! - Code-1");
		glfwTerminate();
		return 1;

	}

	glfwGetFramebufferSize(Window, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(Window);

	CreateCallbacks();
	//glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed - Code-2");
		glfwDestroyWindow(Window);
		glfwTerminate();
		return 1;
	}



	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(Window, this);
}
GLfloat WindowGen::getChangeX()
{
	GLfloat theChange = changeX;
	changeX = 0;
	return theChange;
}

GLfloat WindowGen::getChangeY()
{
	GLfloat theChange = changeY;
	changeY = 0;
	return theChange;
}

WindowGen::~WindowGen()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
}

void WindowGen::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	WindowGen* theWindow = static_cast<WindowGen*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("Pressed %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("Released %d\n", key);
		}
	}
}

void WindowGen::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	WindowGen* theWindow = static_cast<WindowGen*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstTimeMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstTimeMoved = false;
	}

	theWindow->changeX = xPos - theWindow->lastX;
	theWindow->changeY = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("xChange = %0.6f  yChange = %0.6f\n", theWindow->changeX, theWindow->changeY);

}

void WindowGen::CreateCallbacks()
{
	glfwSetKeyCallback(Window, handleKeys);
	glfwSetCursorPosCallback(Window, handleMouse);
}
