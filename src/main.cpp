#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/OpenGL/renderer.h"
#include "Renderer/OpenGL/shader.h"
#include "Renderer/OpenGL/VertexArray.h"
#include "Renderer/OpenGL/VertexBuffer.h"
#include "Renderer/OpenGL/VertexBufferLayout.h"
#include "Renderer/OpenGL/IndexBuffer.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Use OpenGL 3.3 on the Core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "OpenGL Instance", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization failed!\n";
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    {
        vertex_buffer vb; // Create vertex buffer
        vb.Fill(positions, 4 * 2 * sizeof(float)); // Populate vertex buffer
        vertex_array va; // Create vertex array
        vertex_buffer_layout layout; // Create layout
        Push<float>(layout, 2); // Push 2 floats to vertex layout
        va.AddBuffer(vb, layout); // Set vertex attributes

        index_buffer ib(indices, 6); // Create & populate index buffer

        Shader shader("res/shaders/basic.glsl");
        shader.Bind(); // Select shader program

        GLCall(int location = glGetUniformLocation(shader.m_RendererID, "u_Color")); // Get u_Color location
        ASSERT(location != -1); // Make sure u_Color can be found

        va.Unbind(); // Unbind vertex array
        shader.Unbind(); // Clear program selection
        vb.Unbind(); // Unbind vertex buffer
        ib.Unbind(); // Unbind index buffer

        float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));


            va.Bind(); // Bind vertex array
            shader.Bind(); // Select shader
            GLCall(glUniform4f(location, color[0], color[1], color[2], color[3])); // Set color uniform
            vb.Bind(); // Bind vertex buffer
            ib.Bind(); // Bind index buffer

            if (color[0] > 1.0f) {
                increment = -0.05f;
            }
            else if (color[0] < 0.0f) {
                increment = 0.05f;
            }
            color[0] += increment;

            // Draw call
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        shader.Delete();
        ib.Delete();  // These delete functions don't seem to be necesary
        vb.Delete();
    }

    glfwTerminate();
    return 0;
}