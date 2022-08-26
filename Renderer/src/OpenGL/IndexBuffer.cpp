#include "GLCore.h"
#include "IndexBuffer.h"



namespace Renderer { namespace OpenGL {
	index_buffer CreateIndexBuffer(const void* data, unsigned int count)
	{
		index_buffer ib;
		ib.m_Count = count;
		GLCall(glGenBuffers(1, &ib.m_RendererID)); // Generate 1 buffer
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_RendererID)); // Bind index buffer
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib.m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		return ib;
	}
	
	void DeleteIndexBuffer(index_buffer& ib)
	{
	    GLCall(glDeleteBuffers(1, &ib.m_RendererID));
	}
	
	void BindIndexBuffer(index_buffer ib)
	{
	    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_RendererID)); // Bind index buffer
	
	}
	
	void UnbindIndexBuffer()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Unbind index buffer
	}
}}
