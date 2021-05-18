#include "Texture.h"


Texture::Texture() {
	textureId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = nullptr;
}

Texture::Texture(const char* loc) {
	textureId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = loc;
}

void Texture::LoadTexture() {
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth,0);
	if (!texData) {
		printf("Couldn't find the texture data at %s", fileLocation);
		return;
	}

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);


}

void Texture::UseTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::ClearTexture() {
	glDeleteTextures(1, &textureId);
	textureId = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = nullptr;
}




Texture::~Texture() {
	ClearTexture();
}