// Credit to: LearnOpenGL.com

#include "Mesh.h"

Mesh::Mesh(const std::vector<float> centre, const std::vector<float>& vert, const std::vector<unsigned>& ind) {

	for(unsigned i = 0; i < vert.size(); i += 3) { // For each given vertex
		Vertex vertex;
		vertex.Position = glm::vec3(vert[i], vert[i + 1], vert[i + 2]);
		vertex.Normal = glm::vec3(centre[0] + vert[i], centre[1] + vert[i + 1], centre[2] + vert[i + 2]);
		vertex.TexCoords = glm::vec2((i + 3) % 3, (i + 3) % 3);
		this->vertices.push_back(vertex);
	}

	this->indices = ind;
	this->textures = std::vector<Texture> {};

	setup_mesh();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setup_mesh();
}

void Mesh::setup_mesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Vertex Array Pointer using size of Vertex as it contains vertices, normals, and textures. 
	// Applying an offset moves the pointer location to the required section of data
	// It will loop back around to the next specific section using the sizeof(vertex)

	// offsetof(struct, struct_variable) gets the byte value from start of struct to chosen variable

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

	// Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

	// Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

}

void Mesh::Draw(Shader& shader, bool wire) {
	unsigned int diffuse_count = 1;
	unsigned int specular_count = 1;

	if(wire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	for(unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name = textures[i].type;

		// Must be careful here, if it doesn't conform to either "texture_diffuse" or "texture_specular" it will break;
		std::string number = (name == "texture_diffuse") ? std::to_string(diffuse_count++) : std::to_string(specular_count++);

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	// Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}