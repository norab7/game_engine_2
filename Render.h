#pragma once

#include <glad/glad.h>
#include <glfw3.h>
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
#include "GameObject.h"

class Render {
	const char* window_title;
	int window_width;
	int window_height;

	GLFWwindow* window;
	glm::mat4 model, projection, view;

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

	void update(std::vector<GameObject>& game_objects, Shader& shader);
};

/* TODO LIST:
conversion from obj to vertices/entites
import obj
parameterize obj input to renderer

*/