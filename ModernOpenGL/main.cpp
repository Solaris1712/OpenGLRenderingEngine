#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "WindowGen.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"



std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
WindowGen window;
Camera camera;

Texture brickTexture, dirtTexture;
Light directionalLight;
Material mat;

GLfloat deltaTime = 0.f;
GLfloat lastTime = 0.f;

float toRadians = 3.14 / 180;

//Vertex shader
static const char* vShader = "Shaders/shader1.vert";

//Fragment shader
static const char* fShader = "Shaders/shader1.frag";


void calculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] =
	{
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};

	GLfloat vertices[] =
	{
		-1.f,-1.f,-0.6f,      0.f, 0.f,     0.f,0.f,0.f,
		 0.f,-1.f,1.f,      0.5f,0.f,		0.f,0.f,0.f,
		 1.f,-1.f,-0.6f,      1.f, 0.f,		0.f,0.f,0.f,
		 0.f, 1.f,0.f,      0.5f,1.f,		0.f,0.f,0.f
	};

	calculateAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);


}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(shader1);
}

int main()
{
	window = WindowGen(800, 600);
	window.Initialize();
	camera = Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -60.f, 0.f, 5.f, 0.5f);

	CreateObjects();
	CreateShaders();

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTexture();

	directionalLight = Light(1.f,1.f,1.f,0.3f,
							1.f,0.f,0.f,1.f);
	mat = Material(1.f, 32.f);



	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0,
		uniformAmbientIntensity = 0, uniformAmbientColor = 0, uniformDiffuseIntensity = 0, uniformDiffuseDirection = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0,uniformEyePosition = 0;
	
	glm::mat4 projection(1.f);
	projection = glm::perspective(glm::radians(45.f),(GLfloat)window.getBufferWidth() / window.getBufferHeight(), 0.1f, 100.f);

	while (window.getShouldClose())
	{
		

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

        glfwPollEvents();


		camera.KeysControl(window.getKeys(),deltaTime);
		camera.MouseControl(window.getChangeX(), window.getChangeY());
		
		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensity();
		uniformAmbientColor = shaderList[0]->GetAmbientColor();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensity();
		uniformDiffuseDirection = shaderList[0]->GetDiffuseDirection();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensity();
		uniformShininess = shaderList[0]->GetShininess();
		uniformEyePosition = shaderList[0]->GetEyePosition();
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
			
			glm::mat4 model(1.f);
			model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
			//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.f, 1.f, 0.f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			
			directionalLight.UseLight(uniformAmbientColor, uniformAmbientIntensity,uniformDiffuseDirection,uniformDiffuseIntensity);
			
			brickTexture.UseTexture();
			mat.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[0]->RenderMesh();


		glUseProgram(0);

		window.swapBuffers();
	}

	return 0;
}

