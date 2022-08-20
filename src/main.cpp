#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/renderer.h"


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
        shader.Bind();
        shader.SetUniform4f("u_Color", { 0.0f, 0.0f, 0.0f, 1.0f });

        Vec4f color = { 0.0f, 0.0f, 0.0f, 1.0f };
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            Renderer::Clear(); // Clear screen


            shader.Bind(); // Select shader
            shader.SetUniform4f("u_Color", color); // Set color uniform
            vb.Bind(); // Bind vertex buffer

            if (color.f1 > 1.0f) {
                increment = -0.05f;
            }
            else if (color.f1 < 0.0f) {
                increment = 0.05f;
            }
            color.f1 += increment;

            // Draw call
            Renderer::Draw(OPENGL, va, ib, shader);

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