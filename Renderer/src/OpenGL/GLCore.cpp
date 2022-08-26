#include <iostream>

#include "GLCore.h"

namespace Renderer { namespace OpenGL {
    //Renderer::OpenGL

    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (code " << error << ") in " << function << ", " << file << ": line " << line;
            return false;
        }
        return true;
    }

    void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader)
    {
        BindShader(shader);
        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, ib.m_Count, GL_UNSIGNED_INT, nullptr));
        return;
    }
}}