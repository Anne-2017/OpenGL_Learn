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
	glfwInit(); //��ʼ��glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFW_VERSION_MAJOR


	//�������� 
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH ,SCR_HEIGHT, "opengltest", NULL, NULL);
	if (window == NULL) {
		cout << "failed to create glfw window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//���ǻ���Ҫע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//��ʼ��glad  glfwGetProcAddress��glfw���ĵ�ַ
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

	//viewport �ӿڳߴ�
	//glViewport(0, 0, 800, 600);

	
	//�ͷ���ɾ��֮ǰ������Դ
	glfwTerminate();
	return 0;
	
	
}

/*����ͬ��Ҳϣ���ܹ���GLFW��ʵ��һЩ������ƣ������ͨ��ʹ��GLFW�ļ������뺯������ɡ����ǽ���ʹ��GLFW��glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ����¡�
���ǽ�����һ��processInput�����������е�������뱣�����ࡣ*/
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�����ص�������ԭ�����£�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}