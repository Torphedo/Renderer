#pragma once
#include <string>

bool CompileShader(unsigned int type, const std::string& source, unsigned int& id_target);
unsigned int CreateShader(const std::string filepath, unsigned int ID);

struct Shader
{
	unsigned int m_RendererID;
	std::string filepath;
	Shader(std::string path) : filepath(path) // Saving the filepath parameter into the struct for debug purposes
	{
		m_RendererID = CreateShader(filepath, m_RendererID); // Parse, compile, and link the vertex & fragment shaders from a GLSL file.
	}

	void Bind()
	{
		GLCall(glUseProgram(m_RendererID)); // Select shader program
	}

	void Unbind()
	{
		GLCall(glUseProgram(0)); // Unbind shader program
	}

	void Delete()
	{
		glDeleteProgram(m_RendererID); // Delete shader program
	}
};