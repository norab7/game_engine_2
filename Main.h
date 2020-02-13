#pragma once

/* USE BEFORE USING STB_IMAGE */
//#ifndef STB_IMAGE_H
//#define STB_IMAGE_H
//#include <stb_image.h>
//#endif // !STB_IMAGE_H

#include <iostream>
#include <map>
#include <memory>

#include "Render.h"

/* Initial Settings */
const char* WINDOW_NAME = "Game Engine";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

/* Class Instances */
Shader* shader;
const char* vshader = "shader_vertex.vs";
const char* fshader = "shader_fragment.fs";

Render* render;

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
float ms_per_frame = (1.0f/60.0f);
float second_timer = 0.0f;

/* Stats and Analytics */
unsigned frames = 0, updates = 0;

/* Functions */
void setup();
void process_input();
void callback_window_resize(GLFWwindow* window, int w, int h);
void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_mouse_input(GLFWwindow* window, int button, int action, int mods);
void callback_mouse_movement(GLFWwindow* window, double x, double y);
void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv);