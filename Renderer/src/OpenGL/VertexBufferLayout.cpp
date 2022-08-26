#pragma once

#include "VertexBufferLayout.h"
#include "GLCore.h"


namespace Renderer { namespace OpenGL {
	template<typename T>
	void Push(vertex_buffer_layout& layout, unsigned int count)
	{
		static_assert(false);
	}
	
	template<>
	void Push<float>(vertex_buffer_layout& layout, unsigned int count)
	{
		layout.m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		layout.m_Stride += count * GetSizeOfGLType(GL_FLOAT);
	}
	
	template<>
	void Push<unsigned int>(vertex_buffer_layout& layout, unsigned int count)
	{
		layout.m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		layout.m_Stride += count * GetSizeOfGLType(GL_UNSIGNED_INT);
	}
	
	template<>
	void Push<unsigned char>(vertex_buffer_layout& layout, unsigned int count)
	{
		layout.m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		layout.m_Stride += count * GetSizeOfGLType(GL_UNSIGNED_BYTE);
	}
	
	unsigned int GetSizeOfGLType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
}}
