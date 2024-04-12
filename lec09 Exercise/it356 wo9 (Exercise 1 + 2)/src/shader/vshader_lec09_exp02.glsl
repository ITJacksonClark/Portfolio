// Vertex shader for exp02_lec09.cpp
// By Dr. Qi Zhang
// 2/7/24

#version 460 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
