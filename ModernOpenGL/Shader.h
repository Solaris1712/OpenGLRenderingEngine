#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	void CreateFromString(const char* vertexCode,const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensity();
	GLuint GetAmbientColor();
	GLuint GetDiffuseIntensity();
	GLuint GetDiffuseDirection();
	GLuint GetSpecularIntensity();
	GLuint GetShininess();
	GLuint GetEyePosition();

	void UseShader();
	void ClearShader();
	

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel,uniformView,
		uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDiffuseDirection,
		uniformSpecIntensity, uniformShininess,uniformEyePosition;

	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
};

