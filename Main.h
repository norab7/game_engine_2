#pragma once

// Libraries and Header files
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <map>
#include <memory>

#include "Store.h"

/* Window Settings */
GLFWwindow* window;
const char* WINDOW_TITLE = "Game Engine";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1200;
glm::mat4 model, projection, view;

/* Class Instances */
Shader* shader;
const char* vshader = "shader_vertex.vs";
const char* fshader = "shader_fragment.fs";

/* Variables */
bool shut_down = false;
bool KEY_PRESS[1024];
std::pair<float, float> mouse_offset;

bool firstMouse = true;
float lastX = 0.0f, lastY = 0.0f;

float last_time = 0.0f;
float current_time = 0.0f;
float delta_time = 0.0f;
float lag = 0.0f;
float ms_per_frame = (1.0f / 60.0f);
float second_timer = 0.0f;

// Game Objects
std::vector<GameObject*> game_objects;
GameObject* player;
GameObject* lamp;
GameObject* emitter;

/* Stats and Analytics */
unsigned frames = 0, updates = 0;

/* World Variables */
std::vector<GameObject*> level_objects;
const float grid_spacing = 6.0f;
const int LEVEL_WIDTH = 24;
const int LEVEL_DEPTH = 24;
const int LEVEL_HEIGHT = 2;
int world_grid[LEVEL_WIDTH][LEVEL_DEPTH][LEVEL_HEIGHT] = {0};

/* Functions */
void setup();
void setup_grid();
void process_AI();
void render_scene();
void process_input();
void callback_window_resize(GLFWwindow* window, int w, int h);
void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_mouse_input(GLFWwindow* window, int button, int action, int mods);
void callback_mouse_movement(GLFWwindow* window, double x, double y);
void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv);