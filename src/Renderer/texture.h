#pragma once
#include <stb_image.h>
#include "renderer.h"

struct texture
{
	unsigned int RendererID;
	std::string filepath;
	unsigned char* LocalBuffer; // This will hold the texture data
	int width, height, BytesPerPixel;
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	~texture();
};

void CreateTexture(texture& texture, std::string path);