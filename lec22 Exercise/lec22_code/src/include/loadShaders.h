// Header file for loadShaders.cpp
// By Dr. Qi Zhang
// 3/27/24

#ifndef __LOADSHADER_MAT_H__
#define __LOADSHADER_MAT_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static char* readShaderSource(const char* shaderFile);
int loadShader(const char* vShaderFile, const char* fShaderFile);

#endif
