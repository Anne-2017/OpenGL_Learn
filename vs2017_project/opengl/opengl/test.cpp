#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
using namespace std;

int main() {
	glfwInit(); //≥ı ºªØglfw
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFW_VERSION_MAJOR

	GLFWwindow * window = glfwCreateWindow(800, 600, "opengltest", NULL, NULL);
	if (window == NULL) {
		cout << "failed to create glfw window" << endl;
		glfwTerminate;
		return -1;
	}
	glfwMakeContextCurrent(window);

	return 0;
}