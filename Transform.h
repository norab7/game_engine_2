#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Transform {

public:
	glm::mat4 matrix {1};
	glm::vec3 target{0, 0, 0};
	glm::vec3 direction {0,0,1};
	glm::vec3 up {0,1,0};
	glm::vec3 right {1,0,0};
	glm::vec3 front {0,0,-1};


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