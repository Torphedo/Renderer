#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "shader.h"

// Break if function returns false
#define ASSERT(x) if (!(x)) __debugbreak();
// Clear all errors, call function, then check for and print errors
#define GLCall(x) Renderer::OpenGL::GLClearError(); x; ASSERT(Renderer::OpenGL::GLLogCall(#x, __FILE__, __LINE__))

namespace Renderer { namespace OpenGL {
	// Renderer::OpenGL

	bool GLLogCall(const char* function, const char* file, int line);
	void GLClearError();
	void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader);

}}