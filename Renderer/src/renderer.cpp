#include "renderer.h"
#include "OpenGL/VertexBuffer.h"
#include <GLFW/glfw3.h>
#include <iostream>

int CurrentGraphicsAPI = 0;

namespace Renderer {

	GLFWwindow* window;

	int SetupWindow()
	{
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
	}
	bool CloseWindow()
	{
		return glfwWindowShouldClose(window);
	}
	void SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
	void PollEvents()
	{
		glfwPollEvents();
	}
	void Terminate()
	{
		glfwTerminate();
	}

	void SetAPI(int API)
	{
		CurrentGraphicsAPI = API;
	}

	void CreateVertexBuffer(vertex_buffer& vb)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::CreateVertexBuffer(vb); // Generate 1 buffer
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::CreateVertexBuffer(vb); // Generate 1 buffer
			break;
		}
	}

	void DeleteVertexBuffer(vertex_buffer& vb)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::DeleteVertexBuffer(vb); // Delete vertex buffer
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::DeleteVertexBuffer(vb); // Delete vertex buffer
			break;
		}
	}

	void BindVertexBuffer(vertex_buffer vb)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::BindVertexBuffer(vb); // Bind vertex buffer
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::BindVertexBuffer(vb); // Bind vertex buffer
			break;
		}
	}

	void UnbindVertexBuffer()
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::UnbindVertexBuffer(); // Bind vertex buffer
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::UnbindVertexBuffer(); // Bind vertex buffer
			break;
		}
	}

	void FillVertexBuffer(const void* data, unsigned int size)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::FillVertexBuffer(data, size); // Set positions as buffer data
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::FillVertexBuffer(data, size); // Set positions as buffer data
			break;
		}
	}

	void CreateVertexArray(vertex_array& va)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::CreateVertexArray(va);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::CreateVertexArray(va);
			break;
		}
	}

	void DeleteVertexArray(vertex_array& va)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::DeleteVertexArray(va);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::DeleteVertexArray(va);
			break;
		}
	}

	void BindVertexArray(vertex_array va)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::BindVertexArray(va);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::BindVertexArray(va);
			break;
		}
	}

	void UnbindVertexArray()
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::UnbindVertexArray();
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::UnbindVertexArray();
			break;
		}
	}

	void AddBuffer(vertex_array va, const vertex_buffer& vb, const vertex_buffer_layout& layout)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::AddBuffer(va, vb, layout);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::AddBuffer(va, vb, layout);
			break;
		}
	}


	void Draw(const vertex_array& va, const index_buffer& ib, Shader& shader)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::Draw(va, ib, shader);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Draw(va, ib, shader);
			break;
		}
	}

	void Clear()
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::Clear();
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Clear();
			break;
		}
	}
}
