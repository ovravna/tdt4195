// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include <vector>
#include "gloom/shader.hpp"

/* std::vector<float> vertices= { */ 
/* 	-0.6, -0.6, 0, */
/* 	0.6, -0.6, 0, */
/* 	0, 0.6, 0 */


/* 	/1* -0.5f, -0.5f, 0, *1/ */
/* 	/1*  0.0f,  0.5f, 0, *1/ */
/* 	/1*  0.5f, -0.5f, 0 *1/ */
/* }; */
/* std::vector<int> indices = { 2, 1, 0 }; */


std::vector<float> vertices{
									-0.9,-0.9,0,
									0,0.9,0,
									0.5,-0.9,0,
									0.6,-0.9,0,
									0.9,0.9,0,
									0.1,0.9,0
};

std::vector<int> indices{	
	2,1,0,
	3,4,5
};


unsigned int setupVAO(std::vector<float> vertexCoordinates, std::vector<int> indices) {

	unsigned int vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	unsigned int vertexBuffer = 0; 
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArray);

	/* float vertices[] = {1.0, 3.0, 2.0, 5.0, 4.0, 3.0, 2.0, 6.0, 3.0}; */
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCoordinates.size(), vertexCoordinates.data(), GL_STATIC_DRAW); 


	unsigned int index = 1;
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(index);

	unsigned int indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	
	printGLError();
	
	return vertexArray;
}

Gloom::Shader * loadShader() {

	Gloom::Shader * shader; // = new Gloom::Shader();
	shader->attach("gloom/shaders/simple.frag");
	shader->attach("gloom/shaders/simple.vert");
	shader->link();
	return shader;

}

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

	Gloom::Shader * shader = new Gloom::Shader(); // = new Gloom::Shader();
	shader->makeBasicShader("gloom/shaders/simple.frag", "gloom/shaders/simple.vert");

    // Set up your scene here (create Vertex Array Objects, etc.)
	/* unsigned int vertexArray = setupVAO(triangle_vertices, triangle_indices); */
	
	unsigned int vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	unsigned int vertexBuffer = 0; 
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArray);

	/* float vertices[] = {1.0, 3.0, 2.0, 5.0, 4.0, 3.0, 2.0, 6.0, 3.0}; */
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW); 


	unsigned int index = 0;
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(index);

	unsigned int indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	
	printGLError();
	
	shader->activate();


    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }
	shader->deactivate();
	shader->destroy();
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
