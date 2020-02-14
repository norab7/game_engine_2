// Credit to: LearnOpenGL.com

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif // !STB_IMAGE_H

#include "I_Graphics.h"
#include "Mesh.h"
#include "Shader.h"

class Model : public I_Graphics {
	Shader* shader_;
	std::string dir;
	std::vector<Texture> loaded_textures;
	std::vector<Mesh> meshes;

	void load(const std::string& path);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

	unsigned int texture_from_file(const char* path, const std::string& dir, bool gamma = false);
	std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string name);

public:
	Model(const char* dir, Shader* shader);

	void update(GameObject& g) override;
	void receive(int message) override;
	void activate() override;
	void deactivate() override;
};
