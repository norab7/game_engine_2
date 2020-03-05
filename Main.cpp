#define STB_IMAGE_IMPLEMENTATION // Must be done before using stb_image.h
#include "Main.h"
#include <time.h>

GameObject* test = nullptr;

int main(int argc, char** argv) {
	std::cout << "Setting up GLFW and GLAD components" << std::endl;
	setup();

	unsigned x = 20, y = 0, z = 20;
	setup_world(x, y, z);
	setup_maze();
	setup_initial_objects();
	setup_floor();
	setup_a_star(x, y, z);
	setup_boids(x, y, z);
	setup_emitters();
	setup_bouncers(5);

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
			float physics_time = delta_time * ms_per_frame;
			for(unsigned i = 0; i < game_objects.size(); i++) {
				GameObject* g = game_objects[i];

				g->update_physics(physics_time);

				g->update_move(physics_time);

				if(!g->alive) { game_objects.erase(game_objects.begin() + i); }

			}
			for(GameObject* f : flock_objects) { f->update_physics(physics_time); }
			for(GameObject* f2 : flock_objects2) { f2->update_physics(physics_time); }
			for(unsigned i = 0; i < non_self_colide.size(); i++) {
				non_self_colide[i]->update_physics(physics_time);
				if(!non_self_colide[i]->alive) { non_self_colide.erase(non_self_colide.begin() + i); }
			}

			updates++;
			lag -= ms_per_frame;
		}

		// Render Scene
		render_scene();
		frames++;

		glm::vec3 temp = glm::vec3(-10, 20, -10);
		if(glfwGetTime() - second_timer > 1) {
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

void print_vector(const char* name, glm::vec3 v, bool line) {
	std::cout << name << ": (" << v.x << "," << v.y << "," << v.z << ")";
	if(line) { std::cout << std::endl; }
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

void setup_world(const unsigned& x, const unsigned& y, const unsigned& z) {
	std::cout << "Setting up world" << std::endl;
	world = new World(x + 1, y + 1, z + 1);

}

void setup_maze() {
	std::cout << "Setting up Maze" << std::endl;
	for(glm::vec3 v : world->closed) {
		GameObject* g = STORE::OBJECT::FLOOR(glm::vec3(v), &game_objects);
		g->wire = false;
		g->is_static = true;
		game_objects.push_back(g);
	}
}

void setup_initial_objects() {
	std::cout << "Setting up initial Objects" << std::endl;
	player = STORE::OBJECT::PLAYER_PHX(glm::vec3(-10, 20, 15), KEY_PRESS, mouse_offset, &game_objects);
	player->mass = 10.0f;
	game_objects.push_back(player);
	game_objects.push_back(STORE::OBJECT::LAMP(glm::vec3(0, 0, -30)));
}

void setup_floor() {
	std::cout << "Setting up Floor" << std::endl;
	float x_min = -1, x_max = 5;
	float z_min = -1, z_max = 5;

	for(int x = x_min; x < x_max; x++) {
		for(int z = z_min; z < z_max; z++) {
			GameObject* main_floor = STORE::OBJECT::FLOOR_LARGE(glm::vec3(x * 40.0f, -1, z * 40.0f), &game_objects);
			main_floor->is_static = true;
			level_objects.push_back(main_floor);
		}
	}
}

void setup_a_star(const unsigned& x, const unsigned& y, const unsigned& z) {
	std::cout << "Setting up Generic A* search" << std::endl;
	for(unsigned i = 0; i < 4; i++) {
		glm::vec3 start(0);
		glm::vec3 end(0);

		GameObject* g = STORE::OBJECT::LAMP_SEARCH_COLLIDE(glm::vec3(i, 0, i), world, glm::vec3(x - i, y, z - i), &game_objects);
		game_objects.push_back(g);
	}
}

void setup_boids(const unsigned& x, const unsigned& y, const unsigned& z) {
	std::cout << "Setting up flock of boids : also using A* star for paths" << std::endl;
	Pathfinding boid_search = Pathfinding();
	std::vector<glm::vec3> boid_path = boid_search.get_path(world, glm::vec3(0, 0, 0), glm::vec3(x, y, z));

	for(unsigned i = 0; i < 15; i++) {
		unsigned top = 50.0f;
		float bot = 10.0f;
		glm::vec3 boid_pos(((float) (rand() % top)) / bot, (((float) (rand() % top)) / bot), ((float) (rand() % top)) / bot);

		GameObject* boid = STORE::OBJECT::SPARK_BOID_STATIC_PHX(boid_pos, &flock_objects, &game_objects);
		boid->scale(glm::vec3(2));
		flock_objects.push_back(boid);

		GameObject* boid2 = STORE::OBJECT::SPARK_BOID_CUST(boid_pos, &flock_objects2, boid_path);
		boid2->scale(glm::vec3(3));
		flock_objects2.push_back(boid2);
	}
}

void setup_emitters() {
	std::cout << "Setting up random placed emitters" << std::endl;

	game_objects.push_back(STORE::OBJECT::SPARK_EMITTER_PHX(glm::vec3(0, 1, -10), glm::vec3(0.8f, 0.6f, 0), 0.1f, &game_objects));
	game_objects.push_back(STORE::OBJECT::LAMP_EMITTER_PHX(glm::vec3(100, 1, -10), glm::vec3(-0.5f, 0.1f, 0), 1.0f, &game_objects));
	game_objects.push_back(STORE::OBJECT::TV_EMITTER_PHX(glm::vec3(100, 1, -15), glm::vec3(-0.5f, 0.1f, 0), 1.0f, &game_objects));

	game_objects.push_back(STORE::OBJECT::SPARK_EXPLOSION_PHX(glm::vec3(0, 20, 20), glm::vec3(0, 0.6f, 0), 5, &non_self_colide, &game_objects));


}

void setup_bouncers(unsigned max) {
	std::cout << "Setting up Bouncers" << std::endl;
	for(unsigned i = 0; i < max; i++) {
		float rand_index = rand() % world->closed.size();
		glm::vec3 pos(world->closed.at(rand_index));
		pos += glm::vec3(0, world->HEIGHT_ + 20, 0);
		game_objects.push_back(STORE::OBJECT::LAMP_PHX(pos, &game_objects));

		rand_index = rand() % world->open.size();
		pos = (world->open.at(rand_index));
		pos += glm::vec3(0, world->HEIGHT_ + 20, 0);
		game_objects.push_back(STORE::OBJECT::LAMP_PHX(pos, &game_objects));
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
	for(unsigned i = 0; i < flock_objects.size(); i++) {
		flock_objects[i]->update_graphics(delta_time);
		flock_objects2[i]->update_graphics(delta_time);
	}
	for(GameObject* n : non_self_colide) {
		n->update_graphics(delta_time);
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