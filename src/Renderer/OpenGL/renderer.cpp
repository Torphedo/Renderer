#include <iostream>

#include "renderer.h"

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