// A yellow filled-in triangle moved to the top of the screen
// By Dr. Qi Zhang & Jackson Clark
// 2/5/24

#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// Define Vertex Buffer Object (VBO)
unsigned int VBO;


// Declare the Shader Program (shaderProgram)'s ID
// Declare the Shader Program (shaderProgram)'s ID
int programID;


// Define Vertex Array Object (VAO)
// Declare Vertex Array Object (VAO)
unsigned int VAO;

	

void init(void)
{
	//Initialize the shader program id with the created shaderProgram
	// Initialize the shader program id with the created shaderProgram
	programID = loadShader("C:/Users/jc000/Desktop/IT 356/it356 wo6/Code Folders/lec07_code/src/shader/vshader_lec07_01.glsl", "C:/Users/jc000/Desktop/IT 356/it356 wo6/Code Folders/lec07_code/src/shader/fshader_lec07_01.glsl");


	//Set up vertex data 
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, //left  
		0.5f, -0.5f, 0.0f, //right 
		0.0f,  0.5f, 0.0f  //top   
	};


	//Generate the Id for VBO
	glGenBuffers(1, &VBO);


	//Bind the newly created buffer object VBO to the GL_ARRAY_BUFFER target with the glBindBuffer function:
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	//From then on, any buffer calls we make(on the GL_ARRAY_BUFFER target) 
	//will be used to configure the currently bound buffer, VBO
	//We can make a call to the glBufferData function that copies the previously defined 
	//vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	// Activate by calling glUseProgram with the newly created program object 
	// Use the shader program when we want to render an object
	// Activate by calling glUseProgram with the newly created program object 
// Use the shader program when we want to render an object
	glUseProgram(programID);


	//Generate VAO 
	// Generate VAO 
	glGenVertexArrays(1, &VAO);


	//Bind the Vertex Array Object first, 
	//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//As we only have a single VAO, there's no need to bind it every time, 
//But we'll do so to keep things a bit more organized
	glBindVertexArray(VAO);


	//Set the vertex attribute pointers
	//Tell OpenGL how it should interpret the vertex data 
	//Set the vertex attribute pointers
//Tell OpenGL how it should interpret the vertex data 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	//Enable vertex attribute array
	// Enable vertex attribute array
	glEnableVertexAttribArray(0);

}

void display()
{
	//Clear color buffer 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//As we only have a single VAO, there's no need to bind it every time, 
//But we'll do so to keep things a bit more organized
	glBindVertexArray(VAO);

	//Draw our first triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//No need to unbind it every time 
	glBindVertexArray(0);


}

int main()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lec07 Exp01: Draw A Triangle Using Shaders", NULL, NULL);
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

	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

