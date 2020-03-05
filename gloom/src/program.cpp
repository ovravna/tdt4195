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
#include "OBJLoader.hpp"

#include "stb_image.h"

struct VAO {
	unsigned int vao, vertexVBO, indexVBO, colorVBO, normalVBO;
};

Gloom::Shader * loadShader(std::string frag, std::string vert) {
	Gloom::Shader * shader = new Gloom::Shader(); 
	shader->makeBasicShader(frag, vert);
	return shader;

}

unsigned int setupVAO(std::vector<float> vertexCoordinates, std::vector<unsigned int> indices, std::vector<float> rgba, std::vector<float> normals);
unsigned int setupTexture(std::string texFile);

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

    // Set up your scene here (create Vertex Array Objects, etc.)
	/* unsigned int vertexArray = setupVAO(triangle_vertices, triangle_indices); */
	
	Mesh lunar = loadTerrainMesh("gloom/resources/lunarsurface.obj");
	Helicopter heli = loadHelicopterModel("gloom/resources/helicopter.obj");
	auto shader = loadShader("gloom/shaders/simple.frag", "gloom/shaders/simple.vert");
	auto vertexArray = setupVAO(lunar.vertices, lunar.indices, lunar.colours, lunar.normals);
	auto bodyHeliVAO = setupVAO(heli.body.vertices, heli.body.indices, heli.body.colours, heli.body.normals);
	auto mainRotorVAO = setupVAO(heli.mainRotor.vertices, heli.mainRotor.indices, heli.mainRotor.colours, heli.mainRotor.normals);
	auto tailRotorVAO = setupVAO(heli.tailRotor.vertices, heli.tailRotor.indices, heli.tailRotor.colours, heli.tailRotor.normals);
	auto doorVAO = setupVAO(heli.door.vertices, heli.door.indices, heli.door.colours, heli.door.normals);
	/* unsigned int texture = setupTexture("container.jpg"); */




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

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, cam->getModel());
		glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, cam->getProjection());
		glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, cam->getView());

        // Draw your scene here
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		/* glBindTexture(GL_TEXTURE_2D, texture); */

		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, lunar.indices.size(), GL_UNSIGNED_INT, 0);

		/* activateVAO(*bodyHeliVAO); */
		glBindVertexArray(bodyHeliVAO);
		glDrawElements(GL_TRIANGLES, heli.body.indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(mainRotorVAO);
		glDrawElements(GL_TRIANGLES, heli.mainRotor.indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(tailRotorVAO);
		glDrawElements(GL_TRIANGLES, heli.tailRotor.indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(doorVAO);
		glDrawElements(GL_TRIANGLES, heli.door.indices.size(), GL_UNSIGNED_INT, 0);

		/* glDrawArrays(GL_TRIANGLES, 0, 36); */

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
 
unsigned int setupTexture(std::string texFile) {
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
	unsigned char *data = stbi_load(texFile.c_str(), &width, &height, &nrChannels, 0);
	
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

unsigned int setupVAO(std::vector<float> vertexCoordinates, std::vector<unsigned int> indices, std::vector<float> rgba, std::vector<float> normals) {

	
	unsigned int vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	
	unsigned int vertexBuffer = 0; 
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCoordinates.size(), vertexCoordinates.data(), GL_STATIC_DRAW); 

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	unsigned int normalsBuffer = 0;
	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	unsigned int colorBuffer = 0;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rgba.size(), rgba.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	unsigned int indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);






	printGLError();
	
	return vertexArray;
}
