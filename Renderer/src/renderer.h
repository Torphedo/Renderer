#pragma once
#include "OpenGL/GLCore.h"
#include "src/types.h"
#include "OpenGL/shader.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "texture.h"

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

	template<typename T>
	void Push(vertex_buffer_layout& layout, unsigned int count);
	template<>
	void Push<unsigned int>(vertex_buffer_layout& layout, unsigned int count);
	template<>
	void Push<unsigned char>(vertex_buffer_layout& layout, unsigned int count);

	index_buffer CreateIndexBuffer(const void* data, unsigned int count);
	void DeleteIndexBuffer(index_buffer& ib);
	void BindIndexBuffer(index_buffer ib);
	void UnbindIndexBuffer();

	void SetUniform1i(Shader shader, const char* name, int value);
	void SetUniform1f(Shader shader, const char* name, float value);
	void SetUniform4f(Shader shader, const char* name, Vec4f floats);
	void SetUniformMat4f(Shader shader, const char* name, mat4 matrix);
	void CreateShader(const std::string filepath, Shader& shader);
	void BindShader(Shader shader);
	void UnbindShader();
	void DeleteShader(Shader shader);

	void BindTexture(texture tex, unsigned int slot);
	void UnbindTexture();
	void CreateTexture(texture& texture, std::string path);
	void DeleteTexture(texture& tex);

	void SetAPI(int API);
	void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader);
	void Clear();
}
