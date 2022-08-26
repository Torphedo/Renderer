#include "GLCore.h"
#include "IndexBuffer.h"

void UnbindIndexBuffer()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Unbind index buffer
}

index_buffer::index_buffer(const void* data, unsigned int count)
{
	m_Count = count;
	GLCall(glGenBuffers(1, &m_RendererID)); // Generate 1 buffer
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // Bind index buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void index_buffer::Delete()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void index_buffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // Bind index buffer

}

void index_buffer::Unbind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Bind index buffer

}
