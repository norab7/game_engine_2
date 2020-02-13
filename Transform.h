#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Transform {
	glm::mat4 matrix {1};
public:
	Transform();
	~Transform();
	
	// TODO: add in methods for storing and altering positions, rotations, and scaling information.
	glm::mat4 get_matrix();
	const glm::vec3 get_position() const;
	void set_position(glm::vec3 pos);
	void transform(glm::mat4 trans);
	void translate(glm::vec3 trans);
	void rotate(float degrees, glm::vec3 axis, bool radians = false);
	void scale(float scale);
	void scale(glm::vec3 scale);

};