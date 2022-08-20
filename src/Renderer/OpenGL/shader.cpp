#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "renderer.h"
#include "shader.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

ShaderProgramSource LoadShaderFromFile(const std::string& filepath)
{
    std::ifstream shader(filepath);

    typedef enum
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    }shader_type;

    shader_type type = NONE;
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
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
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
        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "") << (type == GL_FRAGMENT_SHADER ? "fragment" : "")
            << " shader!\n" << message << "\n";
        GLCall(glDeleteShader(id_target));
        return false;
    }

    return true;
}

unsigned int CreateShader(const std::string filepath, unsigned int ID)
{
    auto shadersource = LoadShaderFromFile(filepath);
    ID = glCreateProgram(); // Initialize program
    unsigned int vshader;
    unsigned int fshader;
    CompileShader(GL_VERTEX_SHADER, shadersource.VertexSource, vshader); // Compile individual shaders
    CompileShader(GL_FRAGMENT_SHADER, shadersource.FragmentSource, fshader);

    GLCall(glAttachShader(ID, vshader)); // Select shader for linking
    GLCall(glAttachShader(ID, fshader));
    GLCall(glLinkProgram(ID));           // Link into program
    GLCall(glValidateProgram(ID));       // Validate

    GLCall(glDeleteShader(vshader));
    GLCall(glDeleteShader(fshader));
    return ID;
}

unsigned int Shader::GetUniformLocation(const char* name)
{
    if (m_UniformLocations.find(name) != m_UniformLocations.end())
    {
        return m_UniformLocations[name];
    }
    GLCall(unsigned int location = glGetUniformLocation(m_RendererID, name)); // Get u_Color location
    if (location == -1) // Make sure u_Color can be found
    {
        std::cout << "Warning! Uniform " << name << "doesn't exist or was stripped during compilation!";
    }
    m_UniformLocations[name] = location;
    return location;
}

void Shader::SetUniform4f(const char* name, Vec4f floats)
{
    GLCall(glUniform4f(GetUniformLocation(name), floats.f1, floats.f2, floats.f3, floats.f4)); // Set color uniform
}
