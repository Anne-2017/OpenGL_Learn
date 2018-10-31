#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_s.h>
#include <CreateWindow.h>
#include <iostream>
#include <string>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


GlobeValue globalValue;
//"shaderSource/v.glsl", "shaderSource/f.glsl"



int main() {
	
	//GlobeValue *pValue = new GlobeValue();

	//delete pValue;

	float vertices[]{// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
	};
	globalValue.dataLen = sizeof(vertices);
	globalValue.data = new float[globalValue.dataLen];
	memcpy(globalValue.data, vertices, globalValue.dataLen);
	//cout << sizeof(**gb.vertexl);

	CreatWindow(SCR_WIDTH, SCR_HEIGHT,"shaderSource/v.glsl", "shaderSource/f.glsl");
}


