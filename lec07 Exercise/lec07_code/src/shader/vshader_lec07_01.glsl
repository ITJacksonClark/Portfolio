// Vertex shader for exp01_lec07.cpp
// By Dr. Qi Zhang
// 2/5/24

#version 460 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y + 0.5, aPos.z, 1.0);
}


