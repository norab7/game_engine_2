#include "GameObject.h"

/* Component Includes */
#include "I_Graphics.h"
#include "I_Input.h"
#include "I_Camera.h"
#include "I_Physics.h"
#include "I_Emitter.h"
#include "I_AI.h"
#include "I_Collider.h"

// TODO: Find method of dynamically assigning and replacing components without mentioning via named parent class
GameObject::GameObject(glm::vec3 position, I_Graphics* graphics, I_Input* input, I_Camera* camera, I_Physics* physics, I_Emitter* emitter, I_AI* ai, I_Collider* collider)
	: graphics_(graphics), input_(input), camera_(camera), physics_(physics), emitter_(emitter), ai_(ai), collider_(collider) {

	// Linking Interfaces
	set_position(position);
	if(graphics != nullptr) { components.push_back(graphics); }
	if(input != nullptr) { components.push_back(input); }
	if(camera != nullptr) { components.push_back(camera); }
	if(physics != nullptr) { components.push_back(physics); }
	if(emitter != nullptr) { components.push_back(emitter); }
	if(ai != nullptr) { components.push_back(ai); }
	if(collider != nullptr) { components.push_back(collider); has_collision = true; }
}

void GameObject::update_graphics(float& delta) {
	this->delta_time = delta;
	if(graphics_ != nullptr) { graphics_->update(*this); }
}

void GameObject::update_input(float& delta) {
	this->delta_time = delta;
	if(input_ != nullptr) { input_->update(*this); }
	if(camera_ != nullptr) { camera_->update(*this); }
}

void GameObject::update_physics(float& delta) {
	this->delta_time = delta;
	if(physics_ != nullptr) { physics_->update(*this, -1); }
	if(emitter_ != nullptr) { emitter_->update(*this); }
	if(ai_ != nullptr) { ai_->update(*this); }
	if(collider_ != nullptr) { collider_->update(*this); }

	if(life != -1) {
		life -= (delta * 60.0f);
		if(life <= 0) { alive = false; }
	}

}

void GameObject::update_move(float& delta) {
	this->delta_time = delta;
	if(is_static) { return; }

	if(glm::length(velocity) > 0) { at_rest = false; }

	if(!at_rest || glm::length(velocity) == 0) {
		glm::vec3 pos(get_position());

		pos.x += velocity.x; // *delta_time;
		pos.y += velocity.y; // *delta_time;
		pos.z += velocity.z; // *delta_time;

		if(pos.y <= 0.0f) {
			pos.y = 0;
			velocity.y = 0;
			falling = false;
		} else {
			falling = true;
		}

		set_position(pos);
		float air_drag = 0.9f;
		float x_vel = velocity.x;
		float z_vel = velocity.z;

		if(!falling) {
			x_vel *= air_drag;
			z_vel *= air_drag;
		}

		velocity = glm::vec3(x_vel, velocity.y, z_vel);

	}
}

void GameObject::set_velocity(glm::vec3 v) {
	this->velocity = v;
}
void GameObject::set_velocity(float x, float y, float z) {
	this->set_velocity(glm::vec3(x, y, z));
}
void GameObject::add_velocity(glm::vec3 v) {
	this->velocity += v;
}
void GameObject::add_velocity(float x, float y, float z) {
	this->add_velocity(glm::vec3(x, y, z));
}

// TODO: update to allow sending messages to game objects, may require giving them an id to distinguish them
void GameObject::send(std::string component, std::string action) {
	for(unsigned i = 0; i < components.size(); i++) {
		components[i]->receive(component, action);
	}
}

glm::mat4 GameObject::get_matrix() {
	return this->matrix;
}

const glm::vec3 GameObject::get_position() const {
	return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}

void GameObject::set_position(glm::vec3 pos) {
	matrix[3][0] = pos.x;
	matrix[3][1] = pos.y;
	matrix[3][2] = pos.z;
}

void GameObject::transform(glm::mat4 trans) {
	matrix *= trans;
}

void GameObject::translate(glm::vec3 trans) {
	matrix = glm::translate(matrix, trans);
}

void GameObject::rotate(float angle, glm::vec3 axis, bool radians) {
	matrix = glm::rotate(matrix, (radians) ? angle : glm::radians(angle), axis);
}

void GameObject::scale(float scale) {
	matrix = glm::scale(matrix, glm::vec3(scale));
	//bounds->scale(scale);
}

void GameObject::scale(glm::vec3 scale) {
	matrix = glm::scale(matrix, scale);
	//bounds->scale(scale);
}