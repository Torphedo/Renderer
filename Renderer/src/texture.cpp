#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

#include "texture.h"
#include "renderer.h"

texture::~texture()
{
	GLCall(glDeleteTextures(1, &RendererID));
}

void texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
}

void texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void CreateTexture(texture& texture, std::string path)
{
	// Initializing variables
	texture.width = 0;
	texture.height = 0;
	texture.BytesPerPixel = 0;
	texture.LocalBuffer = 0;
	texture.RendererID = 0;

	stbi_set_flip_vertically_on_load(1); // OpenGL expects textures to start from bottom left
	texture.LocalBuffer = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.BytesPerPixel, 4); // Load texture data into LocalBuffer

	GLCall(glGenTextures(1, &texture.RendererID)); // Generate 1 texture and store ID
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.RendererID)); // Bind texture

	// Set upscaling / downscaling filters, wrap modes
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Load in texture data
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.LocalBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (texture.LocalBuffer)
	{
		stbi_image_free(texture.LocalBuffer);
	}
};