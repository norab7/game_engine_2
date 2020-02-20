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

namespace STORE {
	// TODO: Decouple shader from everthing, it's annoying now
	Shader* shader = nullptr;


	namespace GRAPHICS {
		Model* NEW(const char* model) { return new Model(model, shader); }
		Model* LAMP() { return new Model("resources/graphics_objects/lamp_standing.obj", shader); }
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
		PE_Explosion* BASIC_LAMP_EXPLOSION() { return new PE_Explosion(GRAPHICS::LAMP(), PHYSICS::RIGID(), glm::vec3(0, 10, 0), 10, 10, 2); }
	}

	namespace OBJECT {
		GameObject* PLAYER(const bool(&KEY_MAP)[1024], const std::pair<float, float>& offset) { return new GameObject(nullptr, new Player_Keyboard(KEY_MAP), new Player_Camera(offset)); }
		GameObject* LAMP() { return  new GameObject(GRAPHICS::LAMP(), nullptr, nullptr, PHYSICS::RIGID()); }
		GameObject* LAMP_EXPLOSION() {
			return new GameObject(nullptr, nullptr, nullptr, nullptr, EMITTER::BASIC_LAMP_EXPLOSION());
		}
	}
}

/*

	I_Graphics* graphics, I_Input* input, I_Camera* camera, I_Physics* physics, I_Emitter* emitter

	player = new GameObject(nullptr,
		new Player_Keyboard(KEY_PRESS),
		new Player_Camera(mouse_offset));

	lamp = new GameObject(new Model("resources/graphics_objects/lamp_standing.obj", shader),
		nullptr,
		nullptr,
		new Rigid_Body_Physics());

	emitter = new GameObject(nullptr,
		nullptr,
		nullptr,
		nullptr,
		new PE_Explosion(new Model("resources/graphics_objects/lamp_standing.obj", shader),new Rigid_Body_Physics(), glm::vec3(0, 10, 0), 10, 10, true, 1, 2));

*/