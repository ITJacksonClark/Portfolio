// Loads the shaders for the project
// By Dr. Qi Zhang
// 2/5/24

#include "loadShaders.h"

static char* readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[(long long)size + (long long)1];
	fread(buf, (long long)1, (long long)size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

int loadShader(const char* vShaderFile, const char* fShaderFile)
{
	const GLchar *vertexShaderSource = readShaderSource(vShaderFile);
	const GLchar *fragmentShaderSource = readShaderSource(fShaderFile);

	// Build and compile shader program
	
	// ------------------------------------	
	// Compile vertex shader	
	// Declare Vertex shader referenced by an ID
	unsigned int vertexShader;

	// Create the shader with glCreateShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// We attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//Check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// If compilation failed, we should retrieve the error message with glGetShaderInfoLog and print the error message. 
	// If no errors were detected while compiling the vertex shader it is now compiled.
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	// Compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Link shader objects
	//Link shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// we need to attach the previously compiled shaders 
	// to the program object and then link them with glLinkProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	//Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Don't forget to delete the shader objects once we've linked them to 
	// the program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Return the shader program
	return shaderProgram;
}