#include "Material.h"

Material::Material() {

	specularIntensity = 0;
	shininess = 0;

}
Material::Material(GLfloat specInt, GLfloat shine) {

	specularIntensity = specInt;
	shininess = shine;
}

void Material::UseMaterial(GLuint specIntensityLocation, GLuint shininessLocation) {

	glUniform1f(specIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}





Material::~Material() {

}