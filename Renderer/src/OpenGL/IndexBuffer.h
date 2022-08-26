#pragma once

struct index_buffer
{
	unsigned int m_RendererID;
	unsigned int m_Count;
};

namespace Renderer { namespace OpenGL {
	index_buffer CreateIndexBuffer(const void* data, unsigned int count);
	void DeleteIndexBuffer(index_buffer& ib);
	void BindIndexBuffer(index_buffer ib);
	void UnbindIndexBuffer();
}}
