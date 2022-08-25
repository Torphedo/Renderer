#pragma once

#include <GL/glew.h>
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

template<typename T>
void Push(vertex_buffer_layout& layout, unsigned int count);

unsigned int GetSizeOfGLType(unsigned int type);