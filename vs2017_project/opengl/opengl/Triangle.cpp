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
	//glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ���������������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
	//���ǰ���Ҫ��������ɫ�������Բ�����ʽ�ṩ��glCreateShader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//�������Ƕ���һ�����ͱ�������ʾ�Ƿ�ɹ����룬��������һ�����������Ϣ������еĻ�����������Ȼ��������glGetShaderiv����Ƿ����ɹ���
	//�������ʧ�ܣ����ǻ���glGetShaderInfoLog��ȡ������Ϣ��Ȼ���ӡ����
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