#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

typedef unsigned int vertex_array;

void CreateVertexArray(vertex_array& va);
void DeleteVertexArray(vertex_array& va);
void BindVertexArray(vertex_array va);
void UnbindVertexArray();
void AddBuffer(vertex_array va, const vertex_buffer& vb, const vertex_buffer_layout& layout);
