// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include <vector>
#include "gloom/shader.hpp"
#include <math.h>
#include <iostream>
#include <functional>

#include "camera.hpp"
#include "textures.h"

#include "stb_image.h"


/* std::vector<float> vertices = { */ 
/* 	-0.6, -0.6, 0, */
/* 	0.6, -0.6, 0, */
/* 	0, 0.6, 0 */



/* 	/1* -0.5f, -0.5f, 0, *1/ */
/* 	/1*  0.0f,  0.5f, 0, *1/ */
/* 	/1*  0.5f, -0.5f, 0 *1/ */
/* }; */
/* std::vector<int> indices = { 1, 2, 0 }; */

std::vector<float> verts = {

	0.0, 0.1, -0.0,  //0

	-.2, 0.1, -0.,		//1
	.6, 0.1, -0.,		//2
	0.2, -.4, -0.,	//3
	-.5, 0.2, -0.1,	//1
	.5, 0.2, -0.1,		//2
	0., -.3, -0.1,	//3
	-.6, 0, -0.2,	//1
	.6, 0, -0.2,		//2
	0., -.6, -0.2,	//3
	
	/* .6, -.8, -1.2, */
	/* 0,  .4,  0, */
	/* -.8, -.2, 1.2 */
};


std::vector<int> inds = {
	/* 0, 4, 1, */
	/* 0, 2, 4, */
	/* 0, 3, 2, */  
	/* 0, 1, 3, */
	/* 4, 2, 5, */
	1, 3, 2,
	4, 6, 5,
	7, 9, 8
};


std::vector<float> cubeVert = {

	 .5, -.5, -.5, 1, 0,
	 .5,  .5, -.5, 1, 1,
	-.5,  .5, -.5, 0, 1,
	-.5, -.5, -.5, 0, 0,
	 .5, -.5,  .5, 0, 1,
	 .5,  .5,  .5, 0, 1,
	-.5,  .5,  .5, 1, 1,
	-.5, -.5,  .5, 1, 0,
};


std::vector<int> cubeInd = {
	0, 1, 2,
	0, 2, 3,

	0, 4, 5,
	0, 5, 1,

	4, 7, 6, 
	4, 6, 5,

	3, 2, 7, 
	2, 6, 7,

	1, 5, 6,
	1, 6, 2,

	0, 7, 4,
	0, 3, 7,
};

std::vector<float> cols = {
	/* 1, 1, 1, 0.5, */
	1, 0, 0, 0.5,
	1, 0, 0, 0.5,

	0, 1, 0, 0.5,
	0, 1, 0, 0.5,

	0, 0, 1, 0.5, 
	0, 0, 1, 0.5,

	1, 1, 0, 0.5,
	1, 1, 0, 0.5, 

	/* 0, 0, 1, 0.5, */
}; 
std::vector<float> vertices = {
    
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

std::vector<int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};
/* std::vector<float> vertices{ */
/* 									-0.9,-0.9,0, */
/* 									0,0.9,0, */
/* 									0.5,-0.9,0, */
/* 									0.6,-0.9,0, */
/* 									0.9,0.9,0, */
/* 									0.1,0.9,0 */
/* }; */

/* std::vector<int> indices{ */	
/* 	2,1,0, */
/* 	3,4,5 */
/* }; */



Gloom::Shader * loadShader() {

	Gloom::Shader * shader = new Gloom::Shader(); 
	shader->makeBasicShader("gloom/shaders/simple.frag", "gloom/shaders/simple.vert");
	return shader;

}

unsigned int setupVAO(std::vector<float> vertexCoordinates, std::vector<int> indices, std::vector<float> rgba);
unsigned int setupTexture();

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    /* glEnable(GL_CULL_FACE); */
	glDisable(GL_CULL_FACE); 
	/* glFrontFace(GL_CW); */

	/* glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); */  
    // Set default colour after clearing the colour buffer

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.2, 0.2, 0.2, 1);
	auto shader = loadShader();

    // Set up your scene here (create Vertex Array Objects, etc.)
	/* unsigned int vertexArray = setupVAO(triangle_vertices, triangle_indices); */
	
	unsigned int vertexArray = setupVAO(vertices, indices, cols);

	unsigned int texture = setupTexture();


	auto cam = new Camera(window);
	/* glfwSetCursorPosCallback(window, ); */  
	
	shader->activate();

	auto myUniformLocation = glGetUniformLocation(shader->get(), "osilator");
	auto incrementorLocation = glGetUniformLocation(shader->get(), "incrementor");

	auto viewLocation = glGetUniformLocation(shader->get(), "view");
	auto modelLocation = glGetUniformLocation(shader->get(), "model");
	auto projectionLocation = glGetUniformLocation(shader->get(), "projection");

	glad_glUniform1f(myUniformLocation, 0);
	glad_glUniform1f(incrementorLocation, 0);
	

	float x = 0;

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
		x += 0.01;
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* glad_glUniform1f(myUniformLocation, 0.5*sinf(x)); */
		/* glad_glUniform1f(incrementorLocation, x); */

		glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, cam->getModel());
		glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, cam->getProjection());
		glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, cam->getView());

        // Draw your scene here
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vertexArray);
		/* glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0); */
		glDrawArrays(GL_TRIANGLES, 0, 36);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);
		cam->handleKeyboardInput();

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
 
unsigned int setupTexture() {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	
	/* unsigned char * data = (unsigned char*) dog; */
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




	return texture;
}

unsigned int setupVAO(std::vector<float> vertexCoordinates, std::vector<int> indices, std::vector<float> rgba) {

	unsigned int vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	unsigned int vertexBuffer = 0; 
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArray);

	/* float vertices[] = {1.0, 3.0, 2.0, 5.0, 4.0, 3.0, 2.0, 6.0, 3.0}; */
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCoordinates.size(), vertexCoordinates.data(), GL_STATIC_DRAW); 

	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	glEnableVertexAttribArray(2);
	/* glBindBuffer(GL_ARRAY_BUFFER, rgbaVBO); */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	unsigned int rgbaVBO = 0;
	glGenBuffers(1, &rgbaVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rgbaVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rgba.size(), rgba.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, rgbaVBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned int indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	
	printGLError();
	
	return vertexArray;
}
