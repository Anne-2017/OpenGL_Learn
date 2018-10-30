#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<shader_s.h>
#include<iostream>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
using namespace std;


class GlobeValue{
public :
	GlobeValue() {}
	float SCR_WIDTH;
	float SCR_HEIGHT;

};

GlobeValue gb;
 
int CreatWindow(const unsigned int SCR_WIDTH,const unsigned int SCR_HEIGHT,const GLchar *VshaderAddress,const GLchar *FshaderAddress) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learn_opengl", NULL, NULL); 

	if (window == NULL) {
		cout << "fail to create glfw window" << endl;
		glfwTerminate();
		return -1;
	}
	// glfw window creation
   // --------------------
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader(VshaderAddress , FshaderAddress); //you can name your shader files however you like
	
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
	unsigned int VBO;
	unsigned int VAO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	 glBindVertexArray(0);

	// render loop
	// -----------

	while (!glfwWindowShouldClose(window))
	{
		//input 
		processInput(window);
		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0, 3);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	   // -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
