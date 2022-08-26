#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "src/types.h"

#include "src/Renderer/OpenGL/VertexArray.h"
#include "src/Renderer/OpenGL/IndexBuffer.h"
#include "src/Renderer/OpenGL/shader.h"
#include "src/Renderer/texture.h"

enum GraphicsAPI
{
	OPENGL = 0
};

namespace Renderer {

	int SetupWindow();
	bool CloseWindow();
	void SwapBuffers();
	void PollEvents();
	void Terminate();

	void Draw(int API, const vertex_array& va, const index_buffer& ib, Shader& shader);
	void Clear();
}
