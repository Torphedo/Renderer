#include "renderer.h"
#include "VertexBuffer.h"

void UnbindVertexBuffer()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind vertex buffer
}

vertex_buffer::vertex_buffer()
{
    GLCall(glGenBuffers(1, &m_RendererID)); // Generate 1 buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind vertex buffer
}

void vertex_buffer::Fill(const void* data, unsigned int size)
{
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Set positions as buffer data
}

void vertex_buffer::Delete()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void vertex_buffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind vertex buffer
}

void vertex_buffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Bind vertex buffer
}
