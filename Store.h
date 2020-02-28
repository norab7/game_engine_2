#pragma once

// TODO: come back to work on this after fleshing out other components and gameplay, this is secondary
// TODO: come back to work on this after fleshing out other components and gameplay, this is secondary
// TODO: come back to work on this after fleshing out other components and gameplay, this is secondary

#include "Shader.h"
#include "Model.h"

#include "GameObject.h"
#include "Player_Keyboard.h"
#include "Player_Camera.h"
#include "Rigid_Body_Physics.h"
#include "PE_Explosion.h"
#include "AI_Chase.h"
#include "AI_Pathfinder.h"

namespace STORE {
	// TODO: Decouple shader from everthing, it's annoying now
	Shader* shader = nullptr;


	namespace GRAPHICS {
		Model* NEW(const char* model) { return new Model(model, shader); }
		Model* LAMP() { return new Model("resources/graphics_objects/lamp_standing.obj", shader); }
		Model* HOUSE() { return new Model("resources/graphics_objects/shack.obj", shader); }
		Model* FLOOR_SQUARE() { return new Model("resources/graphics_objects/floor_square.obj", shader); }
	}

	namespace INPUT {
		Player_Keyboard* PLAYER_KEYBOARD(const bool(&KEY_MAP)[1024]) { return new Player_Keyboard(KEY_MAP); }
	}

	namespace CAMERA {
		Player_Camera* PLAYER_CAMERA(const std::pair<float, float>& offset) { return new Player_Camera(offset); }
	}

	namespace PHYSICS {
		Rigid_Body_Physics* RIGID() { return new Rigid_Body_Physics(); }
	}

	namespace EMITTER {
		PE_Explosion* BASIC_LAMP_EXPLOSION(glm::vec3 position, glm::vec3 vel) { return new PE_Explosion(position, GRAPHICS::LAMP(), PHYSICS::RIGID(), vel, 4, 4, 2); }
	}

	namespace AI {
		AI_Chase* CHASE(glm::vec3 target, float speed) { return new AI_Chase(target, speed); }
		AI_Pathfinder* PATHFINDER(World* world, glm::vec3 position, glm::vec3 target) { return new AI_Pathfinder(world, position, target); }
	}

	namespace OBJECT {
		// Position, Graphics, Input, Camera, Physics, Emitter, AI

		// Objects
		GameObject* PLAYER(glm::vec3 position, const bool(&KEY_MAP)[1024], const std::pair<float, float>& offset) { return new GameObject(position, nullptr, new Player_Keyboard(KEY_MAP), new Player_Camera(offset)); }
		GameObject* LAMP(glm::vec3 position) { return  new GameObject(position, GRAPHICS::LAMP(), nullptr, nullptr, nullptr); }
		GameObject* LAMP_EXPLOSION(glm::vec3 position, glm::vec3 vel = glm::vec3(0, 10, 0)) { return new GameObject(position, nullptr, nullptr, nullptr, nullptr, EMITTER::BASIC_LAMP_EXPLOSION(position, vel)); }
		GameObject* LAMP_FOLLOW(glm::vec3 position, glm::vec3 target, float speed) { return new GameObject(position, GRAPHICS::LAMP(), nullptr, nullptr, PHYSICS::RIGID(), nullptr, AI::CHASE(target, speed)); }
		GameObject* LAMP_SEARCH(glm::vec3 position, World* world, glm::vec3 target) { return new GameObject(position, GRAPHICS::LAMP(), nullptr, nullptr, nullptr, nullptr, AI::PATHFINDER(world, position, target)); }

		// Level
		GameObject* HOUSE(glm::vec3 position) { return new GameObject(position, GRAPHICS::HOUSE()); }
		GameObject* FLOOR(glm::vec3 position) { return new GameObject(position, GRAPHICS::FLOOR_SQUARE()); }
	}
}
