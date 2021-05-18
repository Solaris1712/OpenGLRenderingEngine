#pragma once

#include <GL/glew.h>
#include "stb_image.h"
class Texture
{
public:	
	Texture();
	Texture(const char* loc);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();


	~Texture();

private:
	GLuint textureId;
	int width, height, bitDepth;
	const char* fileLocation;
};

