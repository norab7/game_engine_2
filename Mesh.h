// Credit to: LearnOpenGL.com

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>>
#include <iostream>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

namespace _Mesh {
	class Mesh {
		unsigned int VAO, VBO, EBO;

		void setup_mesh();

	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		glm::vec3 centre;

		Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures, glm::vec3 average_vertices);

		void Draw(Shader& shader, bool show_bounds = false);

		void randomize_vertices();

	};
}