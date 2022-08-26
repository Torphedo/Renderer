#pragma once
#include <string>

struct texture
{
	unsigned int RendererID;
	std::string filepath;
	unsigned char* LocalBuffer; // This will hold the texture data
	int width, height, BytesPerPixel;
};

namespace Renderer { namespace OpenGL {
	void BindTexture(texture tex, unsigned int slot);
	void UnbindTexture();
	void CreateTexture(texture& texture, std::string path);
	void DeleteTexture(texture& tex);
}}
