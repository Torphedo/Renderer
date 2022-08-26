#pragma once
#include "OpenGL/GLCore.h"
#include "src/types.h"
#include "OpenGL/shader.h"

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

	void CreateVertexBuffer(vertex_buffer& vb);
	void DeleteVertexBuffer(vertex_buffer& vb);
	void BindVertexBuffer(vertex_buffer vb);
	void UnbindVertexBuffer();
	void FillVertexBuffer(const void* data, unsigned int size);

	void CreateVertexArray(vertex_array& va);
	void DeleteVertexArray(vertex_array& va);
	void BindVertexArray(vertex_array va);
	void UnbindVertexArray();
	void AddBuffer(vertex_array va, const vertex_buffer& vb, const vertex_buffer_layout& layout);

	void SetAPI(int API);
	void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader);
	void Clear();
}
