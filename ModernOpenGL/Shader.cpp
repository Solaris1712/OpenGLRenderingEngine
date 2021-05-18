#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to open file. %s doesn't exist!", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::GetViewLocation()
{
	return uniformView;
}
GLuint Shader::GetAmbientIntensity()
{
	return uniformAmbientIntensity;
}
GLuint Shader::GetAmbientColor()
{
	return uniformAmbientColor;
}
GLuint Shader::GetDiffuseIntensity()
{
	return uniformDiffuseIntensity;
}
GLuint Shader::GetDiffuseDirection()
{
	return uniformDiffuseDirection;
}
GLuint Shader::GetSpecularIntensity()
{
	return uniformSpecIntensity;
}
GLuint Shader::GetShininess()
{
	return uniformShininess;
}
GLuint Shader::GetEyePosition()
{
	return uniformEyePosition;
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}



void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Failed to Compile %d shader - Code-6 \n %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(program, theShader);

	return;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Shader program creation failed - Code-3");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Failed to link program - Code-4 \n %s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Failed to validate program - Code-5 \n %s\n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "dLight.ambientIntensity");
	uniformAmbientColor = glGetUniformLocation(shaderID, "dLight.color");
	uniformDiffuseIntensity = glGetUniformLocation(shaderID, "dLight.diffuseIntensity");
	uniformDiffuseDirection = glGetUniformLocation(shaderID, "dLight.direction");
	uniformSpecIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

}

Shader::~Shader()
{
	ClearShader();
}
