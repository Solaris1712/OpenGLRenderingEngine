#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat defaultMoveSpeed, GLfloat defaultTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
    front = glm::vec3(0.f, 0.f, -1.f);

	moveSpeed = defaultMoveSpeed;
	turnSpeed = defaultTurnSpeed;

	Update();
}

void Camera::KeysControl(bool* keys,GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.f)
	{
		pitch = 89.f;
	}
	if (pitch < -89.f)
	{
		pitch = -89.f;
	}

	Update();

}

glm::vec3 Camera::GetCameraPosition()
{
	return position;
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

}

Camera::~Camera()
{

}