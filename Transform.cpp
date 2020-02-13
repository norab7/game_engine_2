#include "Transform.h"

Transform::Transform() {

}

Transform::~Transform() {

}

glm::mat4 Transform::get_matrix() {
	return this->matrix;
}

const glm::vec3 Transform::get_position() const {
	return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}

void Transform::set_position(glm::vec3 pos) {
	// TODO: Double check this work in all cases
	matrix[3][0] = pos.x;
	matrix[3][1] = pos.y;
	matrix[3][2] = pos.z;
}

void Transform::transform(glm::mat4 trans) {
	matrix *= trans;
}

void Transform::translate(glm::vec3 trans) {
	matrix = glm::translate(matrix, trans);
}

void Transform::rotate(float angle, glm::vec3 axis, bool radians) {
	matrix = glm::rotate(matrix, (radians) ? angle : glm::radians(angle), axis);
}

void Transform::scale(float scale) {
	matrix = glm::scale(matrix, glm::vec3(scale));
}

void Transform::scale(glm::vec3 scale) {
	matrix = glm::scale(matrix, scale);
}