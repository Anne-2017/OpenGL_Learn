#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�
//#include <GLFW/glfw3.h>;

#include <string>
#include <fstream> //�������д�ļ�
#include <sstream> //�������ַ�/��ʽת��
#include <iostream>

//using namespace std;


class Shader
{
public:
	// ����ID
	unsigned int ID;
	//1 ��������ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions: ȷ��ifstream���׳��쳣 
		//failbit ������������ַ��������󣬿ɻ��� / badbit ��������������������󣬲��ɻ��� / eofbit �Ѿ������ļ�β / goodbit /��״̬��ȫ����
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			//open file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;
			// read file buffer contents into streams ����ʹ��STL��̵�ʱ����ʱ����뵽��һ��������ָ�����������һ����������������������һ���ļ��������������ʾ���ϣ����ǿ����ü򵥵����д���Ϳ�����ɡ� ifstream infile("test.txt");
            //��cout << infile.rdbuf();
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file handlers
			vShaderFile.close();
			fShaderFile.close();
			//conver stream into stream
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();		
		}
		catch (std::ifstream::failure e) {
			std::cout << "Error::SHADER::file cant not read" << std::endl;
		}

		const char * vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		//2.compile shaders
		unsigned int vertex;
		unsigned int fragment;
		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &fShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");








	}
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif