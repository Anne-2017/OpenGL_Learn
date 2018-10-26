#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const unsigned int width = 800;
const unsigned int height = 1024;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char *fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow*window = glfwCreateWindow(width, height, "opengl", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned  int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned  int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned  int shaderProgramOrange = glCreateProgram();
	unsigned  int shaderProgramYellow = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
	glCompileShader(shaderProgramYellow);

	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);

	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);


	float firstTriangle[] = {
	   -0.9f, -0.5f, 0.0f,  // left 
	   -0.0f, -0.5f, 0.0f,  // right
	   -0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int VBO[2], VAO[2];

	glGenVertexArrays(2, VAO);	//��������2��Vertex Array Object VAO��
	glGenBuffers(2, VBO); 	//��������2��Vertex Buffer Object VBO��

	glBindVertexArray(VAO[0]); //�󶨶�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //��VAO - VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);//DATA ���浽�ڴ� ���޸�

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//��ȡָ�� glVertexAttribPointer��������OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]); //�󶨶�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); //��VAO - VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);//DATA ���浽�ڴ� ���޸�

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//��ȡָ�� glVertexAttribPointer��������OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�Ѵ������Ϊ��ǰ��ɫ
		glUseProgram(shaderProgramOrange);
		//glClearDepth(1.0);//ָ����Ȼ�������ÿ��������Ҫ��ֵ
		//glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ�����
		glBindVertexArray(VAO[0]); //�󶨶�������
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//����������
		glfwPollEvents();//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���


	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glfwTerminate();
	return 0;

}