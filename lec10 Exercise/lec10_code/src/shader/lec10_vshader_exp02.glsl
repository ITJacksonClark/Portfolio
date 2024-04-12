// Vertex shader for lec10_exp02.cpp
// By Dr. Qi Zhang
// 2/12/24

#version 460 core

//The position variable has attribute position 0
layout (location = 0) in vec3 aPos;   
//The color variable has attribute position 1
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float offset_red;
uniform float offset_pos;

void main()
{
    //gl_Position = vec4(aPos, 1.0); 
    gl_Position = vec4(aPos.x - offset_pos, aPos.y, aPos.z, 1.0);

    //Output a color to the fragment shader
    //ourColor = aColor; 
    ourColor = vec3(aColor.r, aColor.g + offset_red, aColor.b - offset_red);
}
