#pragma once

struct vertex_buffer
{
	unsigned int m_RendererID;

	vertex_buffer();
	void Fill(const void* data, unsigned int size);
	void Delete();
	void Bind() const;
	void Unbind() const;
};

void UnbindVertexBuffer();
