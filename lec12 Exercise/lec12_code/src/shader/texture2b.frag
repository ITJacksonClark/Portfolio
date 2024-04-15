// Fragment shader for lec12_exp2.cpp
// By Dr. Qi Zhang
// 2/19/24

#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2) * vec4(ourColor, 1.0);
}

