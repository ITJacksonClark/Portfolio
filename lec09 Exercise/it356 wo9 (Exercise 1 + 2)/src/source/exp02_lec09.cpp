// A filled-in rectangle that turns from dark violet to magenta in a loop
// By Dr. Qi Zhang & Jackson Clark
// 2/7/24

#include "loadShaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Vertex Buffer Object (VBO)
unsigned int VBOs[2];

//Vertex Array Object (VAO)
unsigned int VAOs[2];

//Shader Program (shaderProgram)'s ID
int shaderProgram;

float redVal;
float blueVal;
GLint redDirect;
GLint blueDirect;

void init(void)
{
	redVal = 0.58f;
	blueVal = 0.827f;
	redDirect = 1;
	blueDirect = 1;

	//Return shaderProgram, which is used to set programID
	shaderProgram = loadShader("../../src/shader/vshader_lec09_exp02.glsl",
		"../../src/shader/fshader_lec09_exp02.glsl");



	//Set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
	-0.6f, -0.5f, 0.0f, //left  
	 0.6f, -0.5f, 0.0f, //right 
	-0.6f,  0.5f, 0.0f  //top 
	};

	float vertices2[] = {
	-0.6f,  0.5f, 0.0f, //left  
	 0.6f,  0.5f, 0.0f, //right 
	 0.6f, -0.5f, 0.0f  //bottom
	};




	//Generate VAO and VBO
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);


	//Bind the Vertex Array Object first, 
	//then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOs[0]);



	//Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);



	//Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Use the shader program when we want to render an object
	glUseProgram(shaderProgram);



	//Note that this is allowed; the call to glVertexAttribPointer
	//registered VBO as 

	//the vertex attribute's bound vertex buffer object so afterwards //we can safely unbind
	/*glBindBuffer(GL_ARRAY_BUFFER, 0);*/



	//You can unbind the VAO afterwards, so other VAO calls won't accidentally //modify this VAO, but this rarely happens. Modifying other VAOs requires a //call to glBindVertexArray anyways. 
	//So we generally don't unbind VAOs (nor VBOs) when it's not directly //necessary.
	/*glBindVertexArray(0);*/

	////Draw in wireframe polygons.
	//glLineWidth(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void display()
{
	if (redDirect == 1)
	{
		redVal += 0.000025f;
		if (redVal > 1.0f)
		{
			redDirect = 0;
		}
	}
	else
	{
		redVal -= 0.000025f;
		if (redVal < 0.58f)
		{
			redDirect = 1;
		}
	}

	if (blueDirect == 1)
	{
		blueVal += 0.000025f;
		if (blueVal > 1.0f)
		{
			blueDirect = 0;
		}
	}
	else
	{
		blueVal -= 0.000025f;
		if (blueVal < 0.827f)
		{
			blueDirect = 1;
		}
	}

	//Render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// update shader uniform
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, redVal, 0.0f, blueVal, 1.0f);
	// 0.580, 0.000, 0.827
	// 1.000, 0.000, 1.000

	//Draw our second triangle
	//As we only have a single VAO, there's no need to bind it every time, 
	//But we'll do so to keep things a bit more organized
	glBindVertexArray(VAOs[1]);
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ex02: Draw A Rectangle Using Shaders", NULL, NULL);
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
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

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

