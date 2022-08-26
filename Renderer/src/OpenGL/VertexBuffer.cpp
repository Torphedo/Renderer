#include "GLCore.h"
#include "VertexBuffer.h"

void UnbindVertexBuffer()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind vertex buffer
}

void BindVertexBuffer(vertex_buffer vb)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb)); // Bind vertex buffer
}

void DeleteVertexBuffer(vertex_buffer& vb)
{
    GLCall(glDeleteBuffers(1, &vb));
}

void FillVertexBuffer(const void* data, unsigned int size)
{
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Set positions as buffer data
}

void CreateVertexBuffer(vertex_buffer& vb)
{
    GLCall(glGenBuffers(1, &vb)); // Generate 1 buffer
}

