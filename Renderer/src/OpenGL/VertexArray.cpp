#include "VertexArray.h"
#include "GLCore.h"
#include "src/renderer.h"

void CreateVertexArray(vertex_array& va)
{
	GLCall(glGenVertexArrays(1, &va));
}

void DeleteVertexArray(vertex_array& va)
{
	GLCall(glDeleteVertexArrays(1, &va));
}

void BindVertexArray(vertex_array va)
{
	GLCall(glBindVertexArray(va));
}

void UnbindVertexArray()
{
	GLCall(glBindVertexArray(0));
}

void AddBuffer(vertex_array va, const vertex_buffer& vb, const vertex_buffer_layout& layout)
{
	BindVertexArray(va);
	Renderer::BindVertexBuffer(vb); // Bind vertex buffer
	const auto& elements = layout.m_Elements; // Get layout elements
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) // Loop through every element in the layout
	{
		const auto element = elements[i]; // Variable to hold single element
		GLCall(glEnableVertexAttribArray(i)); // Enable vertex attributes for the element
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.m_Stride, (const void*) offset)); // Set vertex layout
		offset += element.count * GetSizeOfGLType(element.type); // Increment offset by (sizeof(type) * count)
	}
}
