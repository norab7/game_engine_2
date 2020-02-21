#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"

int main(int argc, char** argv) {

	setup();

	// TODO: Change to BETTER container class for all object types so it can be called as a single line and not be built
	player = STORE::OBJECT::PLAYER(glm::vec3(0, 4, 15), KEY_PRESS, mouse_offset);
	lamp = STORE::OBJECT::LAMP(glm::vec3(0, 0, -30));
	emitter = STORE::OBJECT::LAMP_EXPLOSION(glm::vec3(3, 0, -30));

	game_objects.push_back(player);
	game_objects.push_back(lamp);
	game_objects.push_back(emitter);

	while(!shut_down) {
		// Timing
		current_time = glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
		lag += delta_time;

		// Process Input
		process_input();

		static unsigned count = 0;
		bool create = (count++ % 1000 == 0);
		if(create) {
			game_objects.push_back(STORE::OBJECT::LAMP_EXPLOSION(glm::vec3(-3, 0,-30)));
		}

		// Update Things
		while(lag >= ms_per_frame) {
			for(unsigned i = 0; i < game_objects.size(); i++) {
				if(!game_objects[i]->alive) {
					game_objects.erase(game_objects.begin() + i);
				} else {
					game_objects[i]->update(GameObject::UPDATE_TYPE::PHYSICS);
				}
			}
			updates++;
			lag -= ms_per_frame;
		}

		// Render Scene
		render_scene();
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

void render_scene() {
	// Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	projection = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.0f);
	shader->setMat4("projection", projection);


	static unsigned count = 0;
	bool show = (count++ % 100 == -1);
	glm::mat4 view(player->view);
	if(show) { std::cout << "Player->View: " << view[3][0] << "," << view[3][1] << "," << view[3][2] << ")" << std::endl; }
	shader->setMat4("view", player->view);

	for(GameObject* g : game_objects) {
		g->update();
	}

	// Buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	if(glfwWindowShouldClose(window)) {
		glfwTerminate();
	}
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

	player->update(GameObject::UPDATE_TYPE::CAMERA);
}

void callback_mouse_input(GLFWwindow* window, int button, int action, int mods) {

}

void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset) {

}