#include "Light.h"

Light::Light() {

	color = glm::vec3(1.f, 1.f, 1.f);
	ambientIntensity = 1.f;
	direction = glm::vec3(0.f, -1.f, 0.f);
	diffuseIntensity = 0.f;
}
Light::Light(GLfloat red, GLfloat blue, GLfloat green, GLfloat aInt, 
			GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat difInt) {

	color = glm::vec3(red, blue, green);
	ambientIntensity = aInt;
	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = difInt;
}

void Light::UseLight(GLuint ambientColorLocation, GLuint ambientIntensityLocation, 
			GLuint diffuseDirectionLocation, GLuint diffuseIntensityLocation) {

	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(diffuseDirectionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	
}


Light::~Light(){}