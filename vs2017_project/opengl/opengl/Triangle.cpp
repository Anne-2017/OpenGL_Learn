#include <iostream>
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



	


	

	while (!glfwWindowShouldClose(window)) {
	
		
	}
	glfwTerminate();
	return 0;

}




void framerbuffer_size_callback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
}