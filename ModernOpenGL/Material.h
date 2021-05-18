#pragma once

#include <GL/glew.h>
class Material
{
public:

	Material();
	Material(GLfloat specInt, GLfloat shine);
	void UseMaterial(GLuint specIntensityLocation,GLuint shininessLocation);

	~Material();

private:
	
	GLfloat specularIntensity;
	GLfloat shininess;

};

