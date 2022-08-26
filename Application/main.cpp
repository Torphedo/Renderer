#include <iostream>

#include <vector>
#include <string>
#include <unordered_map>

#include "src/renderer.h"

int main(void)
{
    Renderer::SetupWindow();

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
         -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    {
        unsigned int test;
        glGenTextures(1, &test);
        vertex_array va; // Create vertex array

        vertex_buffer_layout layout; // Create layout
        Push<float>(layout, 2); // Push 2D position floats to vertex layout
        Push<float>(layout, 2); // Push texture coordinates to layout

        vertex_buffer vb; // Create vertex buffer
        vb.Fill(positions, 4 * 4 * sizeof(float)); // Populate vertex buffer
        va.AddBuffer(vb, layout); // Set vertex attributes

        index_buffer ib(indices, 6); // Create & populate index buffer

        Shader shader("res/shaders/basic.glsl");
        shader.Bind();
        shader.SetUniform4f("u_Color", { 0.0f, 0.0f, 0.0f, 1.0f });

        texture texture;
        // This is a little distorted because of the difference in aspect ratio
        CreateTexture(texture, "res/textures/gradient.png");
        texture.Bind(0); // Bind to slot 0
        shader.SetUniform1i("u_Texture", 0);

        Vec4f color = { 0.0f, 0.0f, 0.0f, 1.0f };
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!Renderer::CloseWindow())
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
            Renderer::SwapBuffers();

            /* Poll for and process events */
            Renderer::PollEvents();
        }

        shader.Delete();
        ib.Delete();  // These delete functions don't seem to be necesary
        vb.Delete();
    }

    Renderer::Terminate();
    return 0;
}