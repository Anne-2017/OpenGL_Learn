#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_s.h>
#include <CreateWindow.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



//"shaderSource/v.glsl", "shaderSource/f.glsl"


int main() {
	CreatWindow(SCR_WIDTH, SCR_HEIGHT,"shaderSource/v.glsl", "shaderSource/f.glsl");
	
}


