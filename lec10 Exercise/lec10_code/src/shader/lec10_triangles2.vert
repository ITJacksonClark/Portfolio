// Vertex shader for the second triangle in lec10_exp01.cpp
// By Dr. Qi Zhang
// 2/12/24

#version 460 core

layout( location = 0 ) in vec3 vPosition;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}
