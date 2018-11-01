#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<shader_s.h>
#include<iostream>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
using namespace std;

template<class T>
int length(T& arr)
{
	//cout << sizeof(arr[0]) << endl;
	//cout << sizeof(arr) << endl;
	return sizeof(arr) / sizeof(arr[0]);
}


class GlobeValue{
public :

	GlobeValue():data(0),dataLen(0){}
	float SCR_WIDTH;
	float SCR_HEIGHT;
	float * data ;
	int dataLen;
	const GLchar *vertexPath;

	virtual ~GlobeValue()
	{
		 printf("delete a \n");
		if (data != 0)
		{
			delete[] data;
			data = 0;
		}
	}

	//float arr[gb.size];
};

class B: public GlobeValue
{
public:

	B() : GlobeValue()
	{

	}
	~B()
	{
		printf("delete b \n");
	}
};

extern GlobeValue globalValue;

 

int CreatWindow(const unsigned int SCR_WIDTH,const unsigned int SCR_HEIGHT) {
	printf("--------------------\n");
	GlobeValue *pB = new B();
	delete pB;
	printf("--------------------\n");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl", NULL, NULL); 

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
	Shader ourShader(globalValue.vertexPath); //you can name your shader files however you like
	
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------


	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	

    unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
	};
	

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, globalValue.dataLen, globalValue.data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	//销毁解绑buffer
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		//glDrawArrays(GL_TRIANGLES,0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
