// A filled-in triangle where each side is an rgb
// color that can change depending on key presses
// & you can move it left & right with key presses 
// By Dr. Qi Zhang & Jackson Clark
// 2/12/24

#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;
	
//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;



//Shader Program (shaderProgram)'s ID
int shaderProgram;



//Shader adjust variables
//The offset for color changing
float offset_col;


//The offset for position changing
float offset_pos = 0.0f;



void init(void)
{
	//Return shaderProgram, which is used to set programID
	shaderProgram = loadShader("../../src/shader/lec10_vshader_exp02.glsl",
		"../../src/shader/lec10_fshader_exp02.glsl");



	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//positions         //colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //bottom right
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  //top 
	};




	//Generate VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Bind VAO and VBO
	//Bind the Vertex Array Object first, 
//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//Initialize shader adjust variables
	offset_col = 0.0f;



	//Use shderProgram
//We only have a single shader 
//we could also just activate our shader once beforehand if we want to 
	glUseProgram(shaderProgram);

	//Wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Update shader uniform for color changing from CPU program
	int offsetLocation = glGetUniformLocation(shaderProgram, "offset_red");
	glUniform1f(offsetLocation, offset_col);



	//Update shader uniform for position changing from CPU program
	offsetLocation = glGetUniformLocation(shaderProgram, "offset_pos");
	glUniform1f(offsetLocation, offset_pos);



	//Draw the triangle
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);


}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, 
			"Lec10 Exp02: Draw A Triangle Using Shaders", NULL, NULL);
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

		//glfw: swap buffers and poll IO events 
		//(keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Deallocate all resources by deleting VAO and VBO objects
	//Optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);



	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released 
//this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		offset_col += 0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		offset_col = 0.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		offset_pos = 0.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		offset_pos += 0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		offset_pos += -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		offset_col -= 0.01f;
	}
}


//glfw: whenever the window size changed (by OS or user resize) this 
//callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

