#pragma once

#include "src/types.h"
#include "VertexBufferLayout.h"


void CreateVertexArray(vertex_array& va);
void DeleteVertexArray(vertex_array& va);
void BindVertexArray(vertex_array va);
void UnbindVertexArray();
void AddBuffer(vertex_array va, const vertex_buffer& vb, const vertex_buffer_layout& layout);
