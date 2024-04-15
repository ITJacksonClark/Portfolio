// 10 cubes with awesome face textures but only 
// the first, fourth, seventh, and tenth rotate
// By Dr. Qi Zhang & Jackson Clark
// 3/4/24


#include "loadShaders.h"
#include <stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void generateTexture2D(unsigned char *data, int width, int height, int nrChannels);

//Settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

//Declare VBO, VAO, EBO, Shader Program ID, and Two textures
//Vertex Buffer Object (VBO)
unsigned int VBO;
//Vertex Array Object (VAO)
unsigned int VAO;

//Element Buffer Objects
unsigned int EBO;

//Shader Program (shaderProgram)'s ID
unsigned int shaderProgram;

//Two textures
unsigned int texture1, texture2;



//Ten cube positions
glm::vec3 cubePositions[10];



void init(void)
{
	//configure global OpenGL state
	//Enable depth test
	glEnable(GL_DEPTH_TEST);



	//Return shaderProgram, which is used to set the shader program's ID

	shaderProgram = loadShader("../../src/shader/texture1.vert", "../../src/shader/texture1.frag");


	//set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};





	//World space positions of our cubes
	cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
	cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
	cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
	cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
	cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
	cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
	cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);




	//Generate VAO, VBO, and EBO

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	//Bind VAO, VBO, and EBO to array buffer
	//Create and initialize a buffer object's data store for VBO and EBO
	//by loading vertices and indices to graphics memory 
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Arrange data in graphics memory using attribute pointer
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//Load and create the texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//load image, create texture, and generate mipmaps
	int width, height, nrChannels;

	//tell stb_image.h to flip loaded textures on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("../../src/resources/textures/container.jpg",
		&width, &height, &nrChannels, 0);

	generateTexture2D(data, width, height, nrChannels);



	//Load and create the texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//set the texture wrapping parameters
	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//load image, create texture, and generate mipmaps
	data = stbi_load("../../src/resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	generateTexture2D(data, width, height, nrChannels);



	//Transfer texture1 and texture2 to fragment shader
	//Tell OpenGL for each sampler to which texture unit it belongs to 
	//(only has to be done once)

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

}

void display()
{
	//Clear Buffers
	////Render
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// also clear the depth buffer now!
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//Bind textures on corresponding texture units
	//Activate the texture unit first before binding the texture

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);



	//Activate shader
	glUseProgram(shaderProgram);



	//Create transformations
	//make sure to initialize matrix to identity matrix first
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	////Add model matrix
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	////Add view matrix
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	////Add perspective matrix
	//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


	// Add model view and project matrices
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	projection =
		glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);



	//Retrieve the matrix uniform locations
	//glUniformMatrix4fv()
	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projectLoc = glGetUniformLocation(shaderProgram, "projection");


	//Pass them to the shaders (2 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));


	////Render container
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Render container
	/*glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);*/

	//Render boxes
	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < 10; i++)
	{
		//Calculate the model matrix for each object and pass it to the shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);

		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		if (i == 0 || i == 3 || i == 6 || i == 9)
		{
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		}


		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


}

void generateTexture2D(unsigned char *data, int width, int height, int nrChannels)
{
	if (data)
	{
		if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 1) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 2) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Transform a Mixed Texture: Example 1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
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
	glDeleteBuffers(1, &EBO);


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
}

