#pragma once
#include "OpenGL/GLCore.h"
#include "src/types.h"
#include "OpenGL/shader.h"

extern int CurrentGraphicsAPI;

enum API_Names
{
	OPENGL = 0
};

namespace Renderer {

	int SetupWindow();
	bool CloseWindow();
	void SwapBuffers();
	void PollEvents();
	void Terminate();

	void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader);
	void Clear();
}
