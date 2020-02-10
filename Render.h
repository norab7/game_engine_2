#pragma once

#include <glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#include "Shader.h"

namespace _Render {
	class Render {
		const char* window_title;
		int window_width;
		int window_height;

		GLFWwindow* window;
		// unsigned int VBO, VAO, EBO;

		unsigned int vertexShader;
		unsigned int fragmentShader;
		int shaderProgram;

		glm::mat4 model, projection, view;

		// Shader
		Shader* shader;
		const char* vshader = "shader_vertex.vs";
		const char* fshader = "shader_fragment.fs";

		// Timeing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		bool closing = false; // TODO: better way to close

	protected:
	public:
		Render(int width, int height, const char* title);
		~Render();

		GLFWwindow* get_window();
		
		void set_camera(glm::mat4& camera);

		void update();
	};
}

/* TODO LIST:
conversion from obj to vertices/entites
import obj
parameterize obj input to renderer

*/