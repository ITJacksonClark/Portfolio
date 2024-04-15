// A triangle with the awesome face texture on it
// By Dr. Qi Zhang
// 2/19/24

#include "loadShaders.h"

#include <stb_image.h>

#include <iostream>
using namespace std;

//Declear callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;

//Shader Program (shaderProgram)'s ID
unsigned int shaderProgram;


//Texture units: texture1 and texture2
unsigned int texture1, texture2;


//Window width and height
double nWidth, nHeight;

//Display window ratio
float ratio;


void init(void)
{
	nWidth = SCR_WIDTH;
	nHeight = SCR_HEIGHT;

	//Compute the ratio for the display window
	ratio = (float)nHeight / (float)nWidth;


	//Return shaderProgram, which is used to set the shader program's ID
	shaderProgram = loadShader("C:/Users/jc000/Desktop/IT 356/it356 wo12/Code Folders/lec12_code/src/shader/texture1.vert",
		"C:/Users/jc000/Desktop/IT 356/it356 wo12/Code Folders/lec12_code/src/shader/texture1.frag");


	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions                 //colors           //textures 
	   -0.5f * ratio, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, //lower-left corner
		0.5f * ratio, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, //lower-right corner
		0.0f,          0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f  //top-center conrner 
	};


	//Generate VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Bind VAO and VBO to array buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Load data to GPU memory using attribute pointers
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//Create and load a texture 	
	//Generate and bind texture1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//Set the texture wrapping parameters
	//Set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	//load image, create texture, and generate mipmaps
	int width, height, nrChannels;

	//Tell stb_image.h to flip loaded textures on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("C:/Users/jc000/Desktop/IT 356/it356 wo12/Code Folders/lec12_code/src/resources/textures/wall.jpg",
		&width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	//Generate and bind texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Set the texture wrapping parameters
	//Set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//Load image, create texture, and generate mipmaps
	data = stbi_load("C:/Users/jc000/Desktop/IT 356/it356 wo12/Code Folders/lec12_code/src/resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		//note that the awesomeface.png has transparency and thus an alpha channel, 
		//so, make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	//Tell OpenGL for each sampler to which texture unit it belongs to 
//(only has to be done once)
	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind textures on corresponding texture units
//Activate the texture unit first before binding the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Render container
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lec12 Exp1: Draw A Triangle with Mixed Texture", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Set framebuffer_size_callback function using glfw
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		display();

		//glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	//Make sure the viewport matches the new window dimensions; note that the width and 
//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	ratio = (float)height / (float)width;

	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions                 //colors           //textures 
			-0.5f * ratio, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, //lower-left corner
			 0.5f * ratio, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, //lower-right corner
			 0.0f,          0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f  //top-center corner 
	};
	//Recreate the buffer data store using vertices 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

