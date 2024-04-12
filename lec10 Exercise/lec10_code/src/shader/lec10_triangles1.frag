// Fragment shader for the first triangle in lec10_exp01.cpp
// By Dr. Qi Zhang
// 2/12/24

#version 460 core

out vec4 FragColor;
uniform float timeVal;

void main()
{
    FragColor = vec4(abs(sin(timeVal)), 0.4, 0.8, 1.0);
}
