﻿#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framerbuffer_size_callback(GLFWwindow * window, int width, int height);


const char *vertexShaderSource = "#version 330 core\n";
const char *fragmentShaderSource = "#version 300 core\n";


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow*window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"Traingle", NULL, NULL);
	if (window == NULL) {
		cout << "fail to creat glfw window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framerbuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "failed to initialize glad" << endl;
		return -1;
	}
	//----------------------- VERTEX --------------------------------------------------

	// build and compile our shader program
	// ------------------------------------
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
	//我们把需要创建的着色器类型以参数形式提供给glCreateShader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//首先我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器。然后我们用glGetShaderiv检查是否编译成功。
	//如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它。
	int success;
	char infoLog[512];

	//get info and print it 
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "error shader vertex compilation faild \n" << endl;
	}

	//----------------------- fragment  --------------------------------------------------
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "error shader fragment compilation failed \n" << endl;
	}

	//------------------------- Link shader -------------------------------------
	//如果要使用刚才编译的着色器我们必须把它们链接(Link)为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ërror shader program linking failed \n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	//顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	// 0. 复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上） . 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	//第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？
	//它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
	//第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
	//第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
	//第四个参数参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是 - 1）到1之间。我们把它设置为GL_FALSE。
	//第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的
    //（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）
    //最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
	//每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVetexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。
	//由于在调用glVetexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。



	
	
	
	
	while (!glfwWindowShouldClose(window)) {
	
		
	}
	glfwTerminate();
	return 0;

}




void framerbuffer_size_callback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}