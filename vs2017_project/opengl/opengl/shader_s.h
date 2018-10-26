#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream> //常用与读写文件
#include <sstream> //产用于字符/格式转换
#include <iostream>


class Shader
{
public:
	// 程序ID
	unsigned int ID;
	// 构造器读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions: 确保ifstream能抛出异常 
		//failbit 输入输出流出现非致命错误，可换回 / badbit 输入输出流出现致命错误，不可换回 / eofbit 已经到达文件尾 / goodbit /流状态完全正常
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			//open file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;
			// read file buffer contents into streams 我们使用STL编程的时候有时候会想到把一个流对象指向的内容用另一个流对象来输出，比如想把一个文件的内容输出到显示器上，我们可以用简单的两行代码就可以完成。 ifstream infile("test.txt");
            //如cout << infile.rdbuf();
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
		
		
		}






	}
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif