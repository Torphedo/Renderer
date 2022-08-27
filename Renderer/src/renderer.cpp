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
		window = glfwCreateWindow(1280, 720, "OpenGL Instance", NULL, NULL);
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
		return 1;
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

	template<typename T>
	void Push(vertex_buffer_layout& layout, unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(vertex_buffer_layout& layout, unsigned int count)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::Push<float>(layout, count);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Push<float>(layout, count);
			break;
		}
	}

	template<>
	void Push<unsigned int>(vertex_buffer_layout& layout, unsigned int count)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::Push<unsigned int>(layout, count);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Push<unsigned int>(layout, count);
			break;
		}
	}

	template<>
	void Push<unsigned char>(vertex_buffer_layout& layout, unsigned int count)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::Push<unsigned char>(layout, count);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::Push<unsigned char>(layout, count);
			break;
		}
	}

	index_buffer CreateIndexBuffer(const void* data, unsigned int count)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			return OpenGL::CreateIndexBuffer(data, count);
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			return OpenGL::CreateIndexBuffer(data, count);
		}
	}
	void DeleteIndexBuffer(index_buffer& ib)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::DeleteIndexBuffer(ib);
			break;
		default:
			// Default to OpenGL if Graphics API is out of enum's bounds
			OpenGL::DeleteIndexBuffer(ib);
			break;
		}
	}
	void BindIndexBuffer(index_buffer ib)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::BindIndexBuffer(ib);
				break;
			default:
				OpenGL::BindIndexBuffer(ib);
				break;
		}
	}
	void UnbindIndexBuffer()
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::UnbindIndexBuffer();
			break;
		default:
			OpenGL::UnbindIndexBuffer();
			break;
		}
	}

	void SetUniform1i(Shader shader, const char* name, int value)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::SetUniform1i(shader, name, value);
				break;
			default:
				OpenGL::SetUniform1i(shader, name, value);
				break;
		}
	}
	void SetUniform1f(Shader shader, const char* name, float value)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::SetUniform1f(shader, name, value);
				break;
			default:
				OpenGL::SetUniform1f(shader, name, value);
				break;
		}
	}
	void SetUniform4f(Shader shader, const char* name, Vec4f floats)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::SetUniform4f(shader, name, floats);
				break;
			default:
				OpenGL::SetUniform4f(shader, name, floats);
				break;
		}
	}

	void SetUniformMat4f(Shader shader, const char* name, mat4& matrix)
	{
		switch (CurrentGraphicsAPI)
		{
		case OPENGL:
			OpenGL::SetUniformMat4f(shader, name, matrix);
			break;
		default:
			OpenGL::SetUniformMat4f(shader, name, matrix);
			break;
		}
	}

	void CreateShader(const std::string filepath, Shader& shader)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::CreateShader(filepath, shader);
				break;
			default:
				OpenGL::CreateShader(filepath, shader);
				break;
		}
	}
	void BindShader(Shader shader)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::BindShader(shader);
				break;
			default:
				OpenGL::BindShader(shader);
				break;
		}
	}
	void UnbindShader()
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::UnbindShader();
				break;
			default:
				OpenGL::UnbindShader();
				break;
		}
	}
	void DeleteShader(Shader shader)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::DeleteShader(shader);
				break;
			default:
				OpenGL::DeleteShader(shader);
				break;
		}
	}

	void BindTexture(texture tex, unsigned int slot)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::BindTexture(tex, slot);
				break;
			default:
				OpenGL::BindTexture(tex, slot);
				break;
		}
	}
	void UnbindTexture()
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::UnbindTexture();
				break;
			default:
				OpenGL::UnbindTexture();
				break;
		}
	}
	void CreateTexture(texture& texture, std::string path)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::CreateTexture(texture, path);
				break;
			default:
				OpenGL::CreateTexture(texture, path);
				break;
		}
	}
	void DeleteTexture(texture& tex)
	{
		switch (CurrentGraphicsAPI)
		{
			case OPENGL:
				OpenGL::DeleteTexture(tex);
				break;
			default:
				OpenGL::DeleteTexture(tex);
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
