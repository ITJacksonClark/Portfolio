// Fragment shader for exp01_lec09.cpp
// By Dr. Qi Zhang
// 2/7/24

#version 460 core

out vec4 FragColor;
  
//we set this variable in the OpenGL code.
uniform vec4 ourColor; 

void main()
{
    FragColor = ourColor;
} 
