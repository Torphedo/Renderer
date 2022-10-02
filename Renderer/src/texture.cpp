#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"
#include "renderer.h"

namespace Renderer { namespace OpenGL {
	void DeleteTexture(texture& tex)
	{
		GLCall(glDeleteTextures(1, &tex.RendererID));
	}
	
	void BindTexture(texture tex, unsigned int slot)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // Set active texture to specified slot
		GLCall(glBindTexture(GL_TEXTURE_2D, tex.RendererID)); // Bind the specified texture
	}
	
	void UnbindTexture()
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

		// Load texture data from file into LocalBuffer
		texture.LocalBuffer = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.BytesPerPixel, 4);
	
		GLCall(glGenTextures(1, &texture.RendererID)); // Generate 1 texture and store ID
		GLCall(glBindTexture(GL_TEXTURE_2D, texture.RendererID)); // Bind texture
	
		// Set upscaling / downscaling filters, wrap modes
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
		// Load in texture data
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.LocalBuffer));
	
		if (texture.LocalBuffer)
		{
			stbi_image_free(texture.LocalBuffer);
		}
	};
}}
