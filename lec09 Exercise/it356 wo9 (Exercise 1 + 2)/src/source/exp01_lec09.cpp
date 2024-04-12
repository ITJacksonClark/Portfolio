// A filled-in triangle that turns from yellow to black in a loop
// By Dr. Qi Zhang & Jackson Clark
// 2/7/24

#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Vertex Buffer Object (VBO)
unsigned int VBO;

//Vertex Array Object (VAO)
unsigned int VAO;

//Shader Program (shaderProgram)'s ID
int shaderProgram;

void init(void)
{
	//Return shaderProgram, which is used to set programID
	shaderProgram = loadShader("../../src/shader/vshader_lec09_exp01.glsl",
		"../../src/shader/fshader_lec09_exp01.glsl");



	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, //left  
	 0.5f, -0.5f, 0.0f, //right 
	 0.0f,  0.5f, 0.0f  //top   
	};




	//Generate VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Bind the Vertex Array Object first, 
//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);



	//Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	//Use the shader program when we want to render an object
	glUseProgram(shaderProgram);



	//Note that this is allowed; the call to glVertexAttribPointer
//registered VBO as 

//the vertex attribute's bound vertex buffer object so afterwards //we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	//You can unbind the VAO afterwards, so other VAO calls won't accidentally //modify this VAO, but this rarely happens. Modifying other VAOs requires a //call to glBindVertexArray anyways. 
//So we generally don't unbind VAOs (nor VBOs) when it's not directly //necessary.
	glBindVertexArray(0);

	////Draw in wireframe polygons.
	//glLineWidth(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


}

void display()
{
	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// update shader uniform
	float timeValue = glfwGetTime();
	float yellowValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, yellowValue, yellowValue, 0.0f, 1.0f);


	//Draw our first triangle
	//As we only have a single VAO, there's no need to bind it every time, 
	//But we'll do so to keep things a bit more organized
	glBindVertexArray(VAO);
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lec09 Ex01: Jackson", NULL, NULL);
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

	//glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

//Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
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

