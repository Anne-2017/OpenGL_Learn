#version 330 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aColor; 

uniform float offset =0;

out vec3 ourColor; 
out vec3 position;


void main()
{ position = aPos;
   // gl_Position = vec4(aPos.x,-aPos.y,aPos.z, 1.0);
   gl_Position =vec4(position,1)  ;
  
  //  ourColor = aColor; 
}