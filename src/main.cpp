#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ------------------------------- Global definitions -------------------------- //

// ------------------------------ Function definitions ------------------------- //
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int checkShaderCompilation(unsigned int vertexShader, char *infoLog);

int main(void) {
	// -------------------------- GLFW Initialisation -------------------------- //
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	// -------------------------- GLAD Initialisation -------------------------- //
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout <<"Failed to initialise GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ----------------------------- Actual code ------------------------------ //
	// Set the screen size
	glViewport(0, 0, 800, 600); 
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // Set a callback to resize the screen

	// Set up game values	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO;

	unsigned int VAO;
	
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n {"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	unsigned int vertexShader;

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n {"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	unsigned int fragmentShader;

	unsigned int shaderProgram;

	char infoLog[512];
	int success;

	// Creating the VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the vertex array, then buffer, then copy the data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tell OpenGL how to interpret the vertex data and unbind
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	
	// Create the vertex shader, add the source to it and compile it
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader, infoLog);

	// Create the fragment shader, add the source to it and compile
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader, infoLog);

	// Create the shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check shader program link status (TODO export into function)
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILURE" << std::endl << infoLog << std::endl;
	}

	// Delete the vertex and fragment shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// Process user input
		processInput(window);

		// Render shit
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader program and VAO and then print the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// Check and call events and swap the butters
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// End the game
	glfwTerminate();
	return 0;
}


void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int checkShaderCompilation(unsigned int vertexShader, char *infoLog) {
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILURE" << std::endl << infoLog << std::endl;
	}

	return success;
}
