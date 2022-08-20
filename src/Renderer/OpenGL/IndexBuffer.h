#pragma once

struct index_buffer
{
	unsigned int m_RendererID;
	unsigned int m_Count;

	index_buffer(const void* data, unsigned int count); // Run on struct init
	void Delete();
	void Bind();
	void Unbind();
};

void UnbindIndexBuffer();
