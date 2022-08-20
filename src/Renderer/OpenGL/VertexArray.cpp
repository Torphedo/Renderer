#include "VertexArray.h"
#include "GLCore.h"

vertex_array::vertex_array()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

vertex_array::~vertex_array()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void vertex_array::AddBuffer(const vertex_buffer& vb, const vertex_buffer_layout& layout)
{
	Bind();
	vb.Bind(); // Bind vertex buffer
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

void vertex_array::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void vertex_array::Unbind() const
{
	GLCall(glBindVertexArray(0));
}