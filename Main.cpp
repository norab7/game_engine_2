#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"

#include "GameObject.h"
#include "Player_Inputs.h"
#include "Model.h"

std::vector<GameObject> game_objects;
int main(int argc, char** argv) {

	setup();

	game_objects.push_back(*new GameObject(
		new Model("resources/graphics_objects/lamp_standing.obj", shader),
		new Player_Inputs(KEY_PRESS, mouse_offset)
	));

	while(!shut_down) {
		// Timing
		current_time = glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
		lag += delta_time;

		// Process Input
		process_input();
		game_objects[0].update(GameObject::UPDATE_TYPE::INPUT);



		// Update Things
		while(lag >= ms_per_frame) {
			updates++;
			lag -= ms_per_frame;
		}

		// Render Scene
		render->update(game_objects, *shader);
		frames++;


		// Analytics and fps
		if(glfwGetTime() - second_timer > 1) {
			std::cout << "Frames[" << frames << "] : Updates[" << updates << "]" << std::endl;
			second_timer++;
			updates = 0;
			frames = 0;
		}
	}


	std::cout << "Press return to exit";
	std::cin.ignore();
	return 0;
}

void setup() {
	// Timing
	last_time = glfwGetTime();
	second_timer = last_time;

	// Graphics
	render = new Render(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	shader = new Shader(vshader, fshader);

	// Callbacks
	GLFWwindow* window = render->get_window();
	glfwSetWindowSizeCallback(window, callback_window_resize);
	glfwSetKeyCallback(window, callback_keyboard_input);
	glfwSetCursorPosCallback(window, callback_mouse_movement);
	glfwSetMouseButtonCallback(window, callback_mouse_input);
	glfwSetScrollCallback(window, callback_mouse_scroll);
}

void process_input() {

	// TODO: Test to see if faster than main loop
	//for(GameObject& g : game_objects) {
	//	g.update(GameObject::UPDATE_TYPE::INPUT);
	//}
}

void callback_window_resize(GLFWwindow* window, int width, int height) {
	// TODO: handle resizing the window or make fullscreen
}

void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Moved to using bool array as checking for key & press caused choppy input

	if(action == GLFW_PRESS) { KEY_PRESS[key] = true; }
	if(action == GLFW_RELEASE) { KEY_PRESS[key] = false; }

	if(KEY_PRESS[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, true);
		shut_down = true;
	}
}

void callback_mouse_movement(GLFWwindow* window, double xpos, double ypos) {
	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	mouse_offset = std::pair<float, float>(xpos - lastX, lastY - ypos);
	// player->process_mouse_movement(xpos - lastX, lastY - ypos);
	lastX = xpos;
	lastY = ypos;
}

void callback_mouse_input(GLFWwindow* window, int button, int action, int mods) {

}

void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset) {

}