#pragma once
#include "OpenGL/GLCore.h"

enum GraphicsAPI
{
	OPENGL = 0
};

namespace Renderer {

	void Draw(int API, const vertex_array& va, const index_buffer& ib, Shader& shader);
	void Clear();
}