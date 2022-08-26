#include <iostream>

#include <vector>
#include <string>
#include <unordered_map>

#include "src/renderer.h"

int main(void)
{
    Renderer::SetAPI(OPENGL);

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
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vertex_buffer vb = 0;   // Initialize new vertex buffer with an ID of 0
        Renderer::CreateVertexBuffer(vb); // Generate new vertex buffer
        Renderer::BindVertexBuffer(vb);   // Bind buffer
        Renderer::FillVertexBuffer(positions, 4 * 4 * sizeof(float)); // Populate vertex buffer
        
        vertex_buffer_layout layout; // Create layout
        Renderer::Push<float>(layout, 2); // Push texture coordinates to layout
        Renderer::Push<float>(layout, 2); // Push 2D position floats to vertex layout

        vertex_array va;           // Create vertex array ID
        Renderer::CreateVertexArray(va);     // Generate array
        Renderer::AddBuffer(va, vb, layout); // Set vertex attributes

        index_buffer ib = Renderer::CreateIndexBuffer(indices, 6); // Create & populate index buffer

        Shader shader;
        CreateShader("res/shaders/basic.glsl", shader);
        BindShader(shader);
        SetUniform4f(shader, "u_Color", { 0.0f, 0.0f, 0.0f, 1.0f });

        texture texture;
        // This is a little distorted because of the difference in aspect ratio
        CreateTexture(texture, "res/textures/gradient.png");
        texture.Bind(0); // Bind to slot 0
        SetUniform1i(shader, "u_Texture", 0);

        Vec4f color = { 0.0f, 0.0f, 0.0f, 1.0f };
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!Renderer::CloseWindow())
        {
            /* Render here */
            Renderer::Clear(); // Clear screen


            BindShader(shader); // Select shader
            // SetUniform4f(shader, "u_Color", color); // Set color uniform
            Renderer::BindVertexBuffer(vb); // Bind vertex buffer

            if (color.f1 > 1.0f) {
                increment = -0.05f;
            }
            else if (color.f1 < 0.0f) {
                increment = 0.05f;
            }
            color.f1 += increment;

            // Draw call
            Renderer::Draw(va, ib, shader);

            /* Swap front and back buffers */
            Renderer::SwapBuffers();

            /* Poll for and process events */
            Renderer::PollEvents();
        }

        DeleteShader(shader);
        Renderer::DeleteIndexBuffer(ib);
        Renderer::DeleteVertexBuffer(vb);
    }

    Renderer::Terminate();
    return 0;
}