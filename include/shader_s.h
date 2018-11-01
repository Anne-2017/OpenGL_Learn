#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
//#include <GLFW/glfw3.h>;

#include <string>
#include <fstream> //常用与读写文件
#include <sstream> //产用于字符/格式转换
#include <iostream>

using namespace std;

class Shader{
public:
	// 程序ID
	unsigned int ID;
	Shader() {};
	//1 构造器读取并构建着色器
	Shader(const GLchar *vertexPath) {
		//string 类必须包含std内
		std::string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions: 确保ifstream能抛出异常 
		//failbit 输入输出流出现非致命错误，可换回 / badbit 输入输出流出现致命错误，不可换回 / eofbit 已经到达文件尾 / goodbit /流状态完全正常
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		//fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			//open file
			vShaderFile.open(vertexPath);
			//fShaderFile.open(fragmentPath);
			stringstream vShaderStream;
			//std::stringstream fShaderStream;
			// read file buffer contents into streams 我们使用STL编程的时候有时候会想到把一个流对象指向的内容用另一个流对象来输出，比如想把一个文件的内容输出到显示器上，我们可以用简单的两行代码就可以完成。 ifstream infile("test.txt");
            //如cout << infile.rdbuf();
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

	// 使用/激活程序
	void use() {
		glUseProgram(ID);
	}
	// uniform工具函数   c_str这是为了与c语言兼容，在c语言中没有string类型，故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。
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