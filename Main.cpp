#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"
#include <time.h>

GameObject* test = nullptr;

int main(int argc, char** argv) {
	setup_glfw_glad();
	setup_initial_objects();

	std::cout << "Setup Complete : Beginning Game Loop" << std::endl;
	last_time = glfwGetTime();
	second_timer = last_time;


	while(!shut_down) {

		// Timing
		current_time = glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
		lag += delta_time;

		// Process Input
		process_input();

		// Update Physics and Movement
		while(lag >= ms_per_frame) {
			float physics_time = delta_time * ms_per_frame;

			// Physics


			// Movement


			updates++;
			lag -= ms_per_frame;
		}

		// Render Scene
		render_scene();
		frames++;

		if(glfwGetTime() - second_timer > 1) {
			std::cout << "Frames[" << frames << "] : Updates[" << updates << "]" << " GameObjects[" << game_objects.size() << "]" << std::endl;
			second_timer++;
			updates = 0;
			frames = 0;
		}

		// Required to clear buffers and laptop use
		glFlush();
		glFinish();

	}

	std::cout << "Press return to exit";
	std::cin.ignore();
	return 0;
}

void print_vector(const char* name, glm::vec3 v, bool line) {
	std::cout << name << ": (" << v.x << "," << v.y << "," << v.z << ")";
	if(line) { std::cout << std::endl; }
}

void setup_glfw_glad() {
	std::cout << "Setting up GLFW and GLAD components" << std::endl;
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
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // TODO: Include in Model loading
	shader = new Shader(vshader, fshader);

	// Callbacks
	glfwSetWindowSizeCallback(window, callback_window_resize);
	glfwSetKeyCallback(window, callback_keyboard_input);
	glfwSetCursorPosCallback(window, callback_mouse_movement);
	glfwSetMouseButtonCallback(window, callback_mouse_input);
	glfwSetScrollCallback(window, callback_mouse_scroll);
}

void setup_initial_objects() {
	std::cout << "Setting up initial Objects" << std::endl;
	player = new GameObject(glm::vec3(0), nullptr, new Player_Keyboard(KEY_PRESS), new Player_Camera(mouse_offset));
	game_objects.push_back(player);
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