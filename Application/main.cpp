#include <iostream>

#include <vector>
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <Windows.h>

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

        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.625f, 1.625f); // Orthographic projection with 16:9 aspect ratio
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Blank camera transform

        Shader shader;
        Renderer::CreateShader("res/shaders/basic.glsl", shader); // Load and compile shader from source file
        Renderer::BindShader(shader);

        texture texture;
        Renderer::CreateTexture(texture, "res/textures/xp.jpg");
        Renderer::BindTexture(texture, 0); // Bind to slot 0
        Renderer::SetUniform1i(shader, "u_Texture", 0);

        Vec4f color = { 0.0f, 0.0f, 0.0f, 1.0f };
        float increment = 0.05f;

        // X & Y position of the texture
        float controlY = 0.0f;
        float controlX = 0.0f;

        /* Loop until the user closes the window */
        while (!Renderer::CloseWindow())
        {
            /* Render here */
            Renderer::Clear(); // Clear screen


            Renderer::BindShader(shader); // Select shader
            Renderer::BindVertexBuffer(vb); // Bind vertex buffer

            // Basic Windows code for WASD keyboard input
            if (GetKeyState('W') & 0x8000)
            {
                controlY += 0.05f;
            }

            if (GetKeyState('S') & 0x8000)
            {
                controlY -= 0.05f;
            }

            if (GetKeyState('A') & 0x8000)
            {
                controlX -= 0.05f;
            }

            if (GetKeyState('D') & 0x8000)
            {
                controlX += 0.05f;
            }

            // Set model translation to our custom X & Y coords. Depth is irrelevant in 2D orthographic projection.
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(controlX, controlY, 0.0f));

            glm::mat4 ModelViewProjectionMatrix = projection * view * model; // Create MVP matrix

            Renderer::SetUniformMat4f(shader, "u_ModelViewProjectionMatrix", ModelViewProjectionMatrix); // Send matrix to shader

            // Draw call
            Renderer::Draw(va, ib, shader);

            /* Swap front and back buffers */
            Renderer::SwapBuffers();

            /* Poll for and process events */
            Renderer::PollEvents();
        }

        Renderer::DeleteShader(shader);
        Renderer::DeleteIndexBuffer(ib);
        Renderer::DeleteVertexBuffer(vb);
    }

    Renderer::Terminate();
    return 0;
}