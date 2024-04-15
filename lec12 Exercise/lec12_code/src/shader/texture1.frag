// Fragment shader for lec12_exp1.cpp
// By Dr. Qi Zhang
// 2/19/24

#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//Texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
// linearly interpolate between both textures (80% wall, 20% Awesomeface)
FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
