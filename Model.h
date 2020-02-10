// Credit to: LearnOpenGL.com

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#include "Mesh.h"
#include "Shader.h"
using namespace _Mesh;

namespace _Model {
	class Model {
		const char* id;

		std::string dir;
		std::vector<Texture> loaded_textures;
		std::vector<Mesh> meshes;

		// Bounding information, first box is always overall
		void check_min_max(glm::vec3 vertex);
		Mesh process_bounds_mesh();

		void load(const std::string& path);
		void process_node(aiNode* node, const aiScene* scene);
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene);


		unsigned int texture_from_file(const char* path, const std::string& dir, bool gamma = false);
		std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string name);

	protected:
		glm::vec3 bounds_min = glm::vec3(0,0,0);
		glm::vec3 bounds_max = glm::vec3(0,0,0);

	public:
		Model(const char* id, const char* dir);

		const char* get_id();
		void Draw(Shader& shader, bool show_bounds = false);
		void randomize_mesh_vertices();

	};
}