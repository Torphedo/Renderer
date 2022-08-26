#pragma once

typedef unsigned int vertex_buffer;

namespace Renderer { namespace OpenGL {
	// Renderer::OpenGL

	void UnbindVertexBuffer();
	void BindVertexBuffer(vertex_buffer vb);
	void FillVertexBuffer(const void* data, unsigned int size);
	void DeleteVertexBuffer(vertex_buffer& vb);
	void CreateVertexBuffer(vertex_buffer& vb);

}}
