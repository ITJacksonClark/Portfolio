// Fragment shader for example1.cpp & example2.cpp
// By Dr. Qi Zhang
// 4/15/24

#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    FragColor = texture(texture1, vec2(1.0 - TexCoords.x, 1.0 - TexCoords.y));
}
