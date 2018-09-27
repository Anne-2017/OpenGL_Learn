#include <iostream>
//#define GLEW_STATIC
#include <glad\glad.h>
#include <GLFW\glfw3.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	glfwInit(); //初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFW_VERSION_MAJOR


	//创建窗体 
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH ,SCR_HEIGHT, "opengltest", NULL, NULL);
	if (window == NULL) {
		cout << "failed to create glfw window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//初始化glad  glfwGetProcAddress是glfw给的地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "fail to initialize glad" << endl;
		return -1;
	}

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//viewport 视口尺寸
	//glViewport(0, 0, 800, 600);

	
	//释放与删除之前所有资源
	glfwTerminate();
	return 0;
	
	
}

/*我们同样也希望能够在GLFW中实现一些输入控制，这可以通过使用GLFW的几个输入函数来完成。我们将会使用GLFW的glfwGetKey函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下。
我们将创建一个processInput函数来让所有的输入代码保持整洁。*/
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。这个回调函数的原型如下：
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}