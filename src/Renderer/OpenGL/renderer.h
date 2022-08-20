#pragma once
#include <GL/glew.h>

// Break if function returns false
#define ASSERT(x) if (!(x)) __debugbreak();
// Clear all errors, call function, then check for and print errors
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


bool GLLogCall(const char* function, const char* file, int line);
void GLClearError();