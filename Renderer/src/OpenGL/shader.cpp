#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLCore.h"
#include "shader.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

namespace Renderer { namespace OpenGL {
    ShaderProgramSource LoadShaderFromFile(const std::string& filepath)
    {
        std::ifstream shader(filepath);
    
        enum shader_type
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };
    
        int type = NONE;
        std::string line;
        std::stringstream ss[2];
        while (getline(shader, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = FRAGMENT;
                }
            }
            else
            {
                // Put line into corresponding index if there is no #shader present
                ss[(int)type] << line << "\n";
            }
        }
    
        return { ss[0].str(), ss[1].str() }; // Return stringstream as a ShaderProgramSource object
    }
    
    bool CompileShader(unsigned int type, const std::string& source, unsigned int& id_target)
    {
        id_target = glCreateShader(type); // Create OpenGL shader
        const char* src = source.c_str();
        GLCall(glShaderSource(id_target, 1, &src, nullptr)); // Select shader source
        GLCall(glCompileShader(id_target)); // Compile
    
        // Error handling
        int result;
        GLCall(glGetShaderiv(id_target, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(id_target, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)_malloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id_target, length, &length, message));
            std::cout << "Failed to compile ";
            switch (type)
            {
                case GL_VERTEX_SHADER:
                    std::cout << "vertex";
                    break;
                case GL_FRAGMENT_SHADER:
                    std::cout << "fragment";
                    break;
                default:
                    std::cout << "[unknown type]";
                    break;
            }
            std::cout << " shader!\n" << message << "\n";
            GLCall(glDeleteShader(id_target)); // Delete failed shader
            return false;
        }
    
        return true;
    }
    
    void CreateShader(const std::string filepath, Shader& shader)
    {
        auto shadersource = LoadShaderFromFile(filepath);
        shader.filepath = filepath;
        shader.RendererID = glCreateProgram(); // Initialize program
        unsigned int vshader;
        unsigned int fshader;
        CompileShader(GL_VERTEX_SHADER, shadersource.VertexSource, vshader); // Compile individual shaders
        CompileShader(GL_FRAGMENT_SHADER, shadersource.FragmentSource, fshader);
    
        GLCall(glAttachShader(shader.RendererID, vshader)); // Select shaders for linking
        GLCall(glAttachShader(shader.RendererID, fshader));
        GLCall(glLinkProgram(shader.RendererID));           // Link shaders into program
        GLCall(glValidateProgram(shader.RendererID));       // Validate
    
        GLCall(glDeleteShader(vshader)); // Delete shaders from intermediate steps
        GLCall(glDeleteShader(fshader));
        return;
    }
    
    int GetUniformLocation(Shader shader, const char* name)
    {
        // Check if the uniform has already been searched for / found
        if (shader.UniformLocations.find(name) != shader.UniformLocations.end())
        {
            return shader.UniformLocations[name];
        }
    
        GLCall(unsigned int location = glGetUniformLocation(shader.RendererID, name)); // Get uniform location
        if (location == -1)
        {
            std::cout << "Shader warning: Uniform " << name << " doesn't exist or was stripped during compilation!\n";
        }
        shader.UniformLocations[name] = location; // Store the location in the string map so it can be looked up later
        return location;
    }
    
    void SetUniform1i(Shader shader, const char* name, int value)
    {
        GLCall(glUniform1i(GetUniformLocation(shader, name), value));
    }
    
    void SetUniform1f(Shader shader, const char* name, float value)
    {
        GLCall(glUniform1f(GetUniformLocation(shader, name), value));
    }
    
    void SetUniform4f(Shader shader, const char* name, Vec4f floats)
    {
        GLCall(glUniform4f(GetUniformLocation(shader, name), floats.f1, floats.f2, floats.f3, floats.f4));
    }

    void SetUniformMat4f(Shader shader, const char* name, mat4 matrix)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(shader, name), 1, GL_FALSE, &matrix[0][0]));
    }
    
    void BindShader(Shader shader)
    {
        GLCall(glUseProgram(shader.RendererID)); // Select shader program
    }
    
    void UnbindShader()
    {
        GLCall(glUseProgram(0)); // Unbind shader program
    }
    
    void DeleteShader(Shader shader)
    {
        glDeleteProgram(shader.RendererID); // Delete shader program
    }
}}