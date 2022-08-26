#pragma once

#include <vector>

struct VertexAttribute
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

struct vertex_buffer_layout
{
	std::vector<VertexAttribute> m_Elements;
	unsigned int m_Stride;	
	vertex_buffer_layout()
	{
		m_Stride = 0; // Initialize stride on creation
	}
};

namespace Renderer { namespace OpenGL {
	template<typename T>
	void Push(vertex_buffer_layout& layout, unsigned int count);
	template<>
	void Push<float>(vertex_buffer_layout& layout, unsigned int count);
	template<>
	void Push<unsigned int>(vertex_buffer_layout& layout, unsigned int count);
	template<>
	void Push<unsigned char>(vertex_buffer_layout& layout, unsigned int count);
	
	unsigned int GetSizeOfGLType(unsigned int type);
}}
