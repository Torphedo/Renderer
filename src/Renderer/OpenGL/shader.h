#pragma once
#include <string>

#include <src/types.h>
#include <unordered_map>

unsigned int CreateShader(const std::string filepath, unsigned int ID);

struct Shader
{
	unsigned int m_RendererID;
	std::string filepath;
	std::unordered_map<std::string, int> m_UniformLocations;
	Shader(std::string path) : filepath(path) // Saving the filepath parameter into the struct for debug purposes
	{
		m_RendererID = CreateShader(filepath, m_RendererID); // Parse, compile, and link the vertex & fragment shaders from a GLSL file.
	}

	void Bind();
	void Unbind();
	void Delete();

	unsigned int GetUniformLocation(const char* name);
	void SetUniform4f(const char* name, Vec4f floats);
};

