#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"
#include <time.h>

bool go_now = false;

int main(int argc, char** argv) {
	std::cout << "Setting up GLFW and GLAD components" << std::endl;
	setup();

	std::cout << "Setting up world" << std::endl;
	unsigned x = 10, y = 5, z = 10;
	setup_grid(x, y, z);

	std::cout << "Setting up initial Objects" << std::endl;
	player = STORE::OBJECT::PLAYER_PHX(glm::vec3(0, 20, 15), KEY_PRESS, mouse_offset, &game_objects);
	game_objects.push_back(player);
	game_objects.push_back(STORE::OBJECT::LAMP(glm::vec3(0, 0, -30)));
	//game_objects.push_back(STORE::OBJECT::LAMP_SEARCH(glm::vec3(0), world, glm::vec3(x, y, z)));
	game_objects.push_back(STORE::OBJECT::LAMP_SEARCH_COLLIDE(glm::vec3(0), world, glm::vec3(x, y, z), &game_objects));
	game_objects.push_back(STORE::OBJECT::LAMP_SEARCH_COLLIDE(glm::vec3(x, 0, 0), world, glm::vec3(0), &game_objects));
	game_objects.push_back(STORE::OBJECT::LAMP_SEARCH_COLLIDE(glm::vec3(2, 0, 0), world, glm::vec3(x, 0, 0), &game_objects));


	GameObject* static_lamp = STORE::OBJECT::LAMP_PHX_COLLIDE(glm::vec3(0, 0, -20), &game_objects);
	static_lamp->is_static = true;
	game_objects.push_back(static_lamp);
	game_objects.push_back(STORE::OBJECT::LAMP_PHX_COLLIDE(glm::vec3(0, 100, -20), &game_objects));


	std::cout << "Setup Complete : Beginning Game Loop" << std::endl;
	last_time = glfwGetTime();
	second_timer = last_time;

	/* Temp things */
	glm::vec3 TEMP_TARGET = glm::vec3(0, 10, 0);

	while(!shut_down) {

		// Timing
		current_time = glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
		lag += delta_time;

		// Process Input
		process_input();

		// Update Things
		while(lag >= ms_per_frame) {
			for(unsigned i = 0; i < game_objects.size(); i++) {
				GameObject* g = game_objects[i];

				float physics_time = delta_time * ms_per_frame;
				g->update_physics(physics_time);

				g->update_move(physics_time);

				if(!g->alive) { game_objects.erase(game_objects.begin() + i); }

			}
			updates++;
			lag -= ms_per_frame;
		}

		// Render Scene
		render_scene();
		frames++;

		// Analytics and fps
		glm::vec3 temp = glm::vec3(player->get_position());
		if(glfwGetTime() - second_timer > 1) {

			if(game_objects.size() < 150) {
				game_objects.push_back(STORE::OBJECT::LAMP_PHX_FOLLOW(glm::vec3(0, 30, -30), temp, 0.01, &game_objects));
			}
			std::cout << "Frames[" << frames << "] : Updates[" << updates << "]" << " GameObjects[" << game_objects.size() << "]" << std::endl;
			second_timer++;
			updates = 0;
			frames = 0;
		}

		glFlush();
		glFinish();

	}

	std::cout << "Press return to exit";
	std::cin.ignore();
	return 0;
}

void setup() {
	srand(time(NULL));

	// Graphics
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	try {
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
		if(window == NULL) { std::cout << "GLFW window failed to create" << std::endl; }
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) { std::cout << "GLAD failed to initialize" << std::endl; }
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	} catch(const std::exception & e) {
		std::cout << "Render::init(): " << e.what() << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Uncomment for Wireframe
	shader = new Shader(vshader, fshader);
	STORE::shader = shader;

	// Callbacks
	glfwSetWindowSizeCallback(window, callback_window_resize);
	glfwSetKeyCallback(window, callback_keyboard_input);
	glfwSetCursorPosCallback(window, callback_mouse_movement);
	glfwSetMouseButtonCallback(window, callback_mouse_input);
	glfwSetScrollCallback(window, callback_mouse_scroll);
}

void setup_grid(const unsigned& x, const unsigned& y, const unsigned& z) {
	world = new World(x + 1, y + 1, z + 1);



	for(glm::vec3 v : world->open) {
		GameObject* g = STORE::OBJECT::FLOOR(glm::vec3(v), &game_objects);
		g->wire = true;
		game_objects.push_back(g);
		// level_objects.push_back(STORE::OBJECT::FLOOR(glm::vec3(v)));
	}

}

void render_scene() {
	// Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	projection = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.0f);
	shader->setMat4("projection", projection);
	//player->update(GameObject::UPDATE_TYPE::CAMERA);
	shader->setMat4("view", glm::translate(player->view, glm::vec3(0, -3, 0)));

	for(GameObject* g : game_objects) {
		g->update_graphics(delta_time);
	}
	for(GameObject* b : level_objects) {
		b->update_graphics(delta_time);
	}

	// Buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	if(glfwWindowShouldClose(window)) {
		glfwTerminate();
	}
}

void process_input() {

	if(KEY_PRESS[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, true);
		shut_down = true;
	}

	player->update_input(delta_time);

}

void callback_window_resize(GLFWwindow* window, int width, int height) {
	// TODO: handle resizing the window or make fullscreen
}

void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Moved to using bool array as checking for key & press caused choppy input

	if(action == GLFW_PRESS) { KEY_PRESS[key] = true; }
	if(action == GLFW_RELEASE) { KEY_PRESS[key] = false; }
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

	//player->update(GameObject::UPDATE_TYPE::CAMERA);
}

void callback_mouse_input(GLFWwindow* window, int button, int action, int mods) {

}

void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset) {

}