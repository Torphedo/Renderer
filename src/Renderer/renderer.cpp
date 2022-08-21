#include "renderer.h"

namespace Renderer {

	void Draw(int API, const vertex_array& va, const index_buffer& ib, Shader& shader)
	{
		switch (API)
		{
		case OPENGL:
			OpenGL::Draw(va, ib, shader);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Draw(va, ib, shader);
			break;
		}
		return;
	}

	void Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}