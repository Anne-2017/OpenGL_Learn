#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
//#include <GLFW/glfw3.h>;

#include <string>
#include <fstream> //�������д�ļ�
#include <sstream> //�������ַ�/��ʽת��
#include <iostream>

using namespace std;

class Shader{
public:
	// ����ID
	unsigned int ID;
	Shader() {};
	//1 ��������ȡ��������ɫ��
	Shader(const GLchar *vertexPath) {
		//string ��������std��
		std::string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions: ȷ��ifstream���׳��쳣 
		//failbit ������������ַ��������󣬿ɻ��� / badbit ��������������������󣬲��ɻ��� / eofbit �Ѿ������ļ�β / goodbit /��״̬��ȫ����
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		//fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			//open file
			vShaderFile.open(vertexPath);
			//fShaderFile.open(fragmentPath);
			stringstream vShaderStream;
			//std::stringstream fShaderStream;
			// read file buffer contents into streams ����ʹ��STL��̵�ʱ����ʱ����뵽��һ��������ָ�����������һ����������������������һ���ļ��������������ʾ���ϣ����ǿ����ü򵥵����д���Ϳ�����ɡ� ifstream infile("test.txt");
            //��cout << infile.rdbuf();
			vShaderStream << vShaderFile.rdbuf();


			string sliper = "CG_FRAGMENT_SHADER";
			string stringData = vShaderStream.str();

			int sliperLen = sliper.size();
			int id = stringData.find(sliper);

			if (id < 0)
			{
				printf("can not found  sliper");
				return;
			}
			vertexCode = stringData.substr(0, id);
			fragmentCode = stringData.substr(id + sliperLen);
		

			//conver stream into stream
			//vertexCode = vShaderStream.str();
			//fragmentCode = fShaderStream.str();		
			//fShaderStream << fShaderFile.rdbuf();
			//close file handlers
			vShaderFile.close();
			//fShaderFile.close();

		}
		catch (ifstream::failure e) {
			cout << "Error::SHADER::file cant not read" << endl;
		}

		const char * vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();

		cout << "vertex shader\n" << vShaderCode << endl;
		cout << "fragment shader\n" << fShaderCode << endl;
		//2.compile shaders
		unsigned int vertex;
		unsigned int fragment;
		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//shaderprogram

	    ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// ʹ��/�������
	void use() {
		glUseProgram(ID);
	}
	// uniform���ߺ���   c_str����Ϊ����c���Լ��ݣ���c������û��string���ͣ��ʱ���ͨ��string�����ĳ�Ա����c_str()��string ����ת����c�е��ַ�����ʽ��
	void setBool(const string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

///////check compile errors
private:
	void checkCompileErrors(unsigned int shader, string type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				{
				 	cout << "Error::shader_compilation_error of type" << type << "\n" << infoLog << "\n----------------------------" << endl;
 			   	}
			}
			else {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					{
						cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- ----------------- -- " << endl;					
					}
				}
			
			}
		}
	
	}

};

#endif