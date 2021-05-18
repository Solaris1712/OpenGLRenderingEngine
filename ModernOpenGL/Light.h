#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red,GLfloat blue, GLfloat green, GLfloat aInt,GLfloat xDir,GLfloat yDir,GLfloat zDir,GLfloat difInt);

	void UseLight(GLuint ambientColorLocation, GLuint ambientIntensityLocation, GLuint diffuseDirectionLocation,GLuint diffuseIntensityLocation);

	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
	glm::vec3 direction;
	GLfloat diffuseIntensity;

};

