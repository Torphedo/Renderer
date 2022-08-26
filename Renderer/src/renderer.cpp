#include "renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>

int GraphicsAPI = 0;

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
		return;
	}

	void Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}