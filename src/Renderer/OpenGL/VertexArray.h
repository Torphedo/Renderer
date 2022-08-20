#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


struct vertex_array
{
	vertex_array();
	~vertex_array();
	void AddBuffer(const vertex_buffer& vb, const vertex_buffer_layout& layout);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};