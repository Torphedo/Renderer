#pragma once
#include <string>
#include <unordered_map>

#include "src/types.h"

struct Shader
{
	unsigned int RendererID;
	std::string filepath; // Path to shader source, in case it's needed later
	
	// Map of uniform locations that have already been found, so that
	// we don't need to search for the same thing multiple times
	std::unordered_map<std::string, int> UniformLocations;
};

int GetUniformLocation(Shader shader, const char* name);
void SetUniform1i(Shader shader, const char* name, int value);
void SetUniform1f(Shader shader, const char* name, float value);
void SetUniform4f(Shader shader, const char* name, Vec4f floats);
void CreateShader(const std::string filepath, Shader& shader);
void BindShader(Shader shader);
void UnbindShader();
void DeleteShader(Shader shader);
