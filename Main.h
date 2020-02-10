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

/* Variables */
_Render::Render* render;

bool shut_down = false;
bool KEY_PRESS[1024];

const char* WINDOW_NAME = "Game Engine";
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

bool firstMouse = true;
float lastX = 0;
float lastY = 0;

/* Functions */
void setup();
void process_input();
void callback_window_resize(GLFWwindow* window, int w, int h);
void callback_keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void callback_mouse_input(GLFWwindow* window, int button, int action, int mods);
void callback_mouse_movement(GLFWwindow* window, double x, double y);
void callback_mouse_scroll(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv);