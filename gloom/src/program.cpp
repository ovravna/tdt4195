// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include <vector>
#include "gloom/shader.hpp"
#include <math.h>
#include <iostream>
#include <functional>

#include "camera.hpp"
#include "sceneGraph.hpp"
#include "textures.h"
#include "OBJLoader.hpp"

#include "stb_image.h"
#include "toolbox.hpp"

Camera * cam;
int viewLocation;
int modelLocation;
int projectionLocation;

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

void drawSceneNode(SceneNode* root, glm::mat4 viewProjectionMatrix) {

	auto model = root->currentTransformationMatrix;
	glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glad_glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, cam->getProjection());
	glad_glUniformMatrix4fv(viewLocation, 1, GL_FALSE, cam->getView());

	if (root->vertexArrayObjectID != -1) {
		glBindVertexArray(root->vertexArrayObjectID);
		glDrawElements(GL_TRIANGLES, root->VAOIndexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	
	for (SceneNode* child : root->children) {
		drawSceneNode(child, viewProjectionMatrix);
	}
}


void updateSceneNode(SceneNode* node, glm::mat4 transformationThusFar) {
	// Do transformation computations here
	
	
	auto mat = transformationThusFar;

	auto pos = node->position + node->referencePoint;

	mat = glm::translate(mat, pos);
	mat = glm::rotate(mat, node->rotation.x, glm::vec3(1, 0, 0)); 
	mat = glm::rotate(mat, node->rotation.y, glm::vec3(0, 1, 0)); 
	mat = glm::rotate(mat, node->rotation.z, glm::vec3(0, 0, 1)); 
	mat = glm::translate(mat, -pos);

	/* node->currentTransformationMatrix *= mat; */
	node->currentTransformationMatrix = glm::translate(mat, node->position);


	
	

	
	// Store matrix in the node's currentTransformationMatrix here
	/* node->position = glm::vec3(0); */
	/* node->rotation = glm::vec3(0); */
	

	auto combinedTransformation = node->currentTransformationMatrix;
	
	for(SceneNode* child : node->children) {
		updateSceneNode(child, combinedTransformation);
	}
}


SceneNode * initSceneNode(SceneNode * parent, Mesh mesh = Mesh("None"), glm::vec3 position = glm::vec3(0), glm::vec3 reference = glm::vec3(0)) {

	SceneNode * node = createSceneNode();

	if (parent == nullptr)
		node->vertexArrayObjectID = -1;
	else {
		node->vertexArrayObjectID = setupVAO(mesh.vertices, mesh.indices, mesh.colours, mesh.normals); 
		node->position = position;
		/* node->position = glm::vec3(mesh.vertices[0], mesh.vertices[1], mesh.vertices[2]); */
		node->VAOIndexCount = mesh.indices.size();
		node->referencePoint = reference;
		node->rotation = glm::vec3(0, 0, 0);

		glm::mat4x4 mat = glm::mat4x4(1);
		/* mat = glm::translate(mat, node->position); */

		node->currentTransformationMatrix = mat;
		addChild(parent, node);
	}

	return node;
	
}

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);
	/* glDisable(GL_CULL_FACE); */ 
	/* glFrontFace(GL_CW); */

	/* glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); */  
    // Set default colour after clearing the colour buffer

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.2, 0.2, 0.2, 1);

    // Set up your scene here (create Vertex Array Objects, etc.)
	
	Mesh lunar = loadTerrainMesh("gloom/resources/lunarsurface.obj");
	Helicopter heli = loadHelicopterModel("gloom/resources/helicopter.obj");
	auto shader = loadShader("gloom/shaders/simple.frag", "gloom/shaders/simple.vert");
	
	auto rootNode = initSceneNode(nullptr);

	auto terrainNode = initSceneNode(rootNode, lunar, glm::vec3(0), glm::vec3(0));
	auto heliBodyNode = initSceneNode(terrainNode, heli.body, glm::vec3(0, 0, 5), glm::vec3(0.104737,-0.156937,2.063079));
	auto heliMainRotorNode = initSceneNode(heliBodyNode, heli.mainRotor, glm::vec3(0), glm::vec3(0));
	/* auto heliTailRotorNode = initSceneNode(heliBodyNode, heli.tailRotor, glm::vec3(0, 0, 0), glm::vec3(0.323498,2.550585,10.231632)); */
	auto heliTailRotorNode = initSceneNode(heliBodyNode, heli.tailRotor, glm::vec3(0), glm::vec3(0.35, 2.3, 10.4));
	auto heliDoorNode = initSceneNode(heliBodyNode, heli.door, glm::vec3(0), glm::vec3(1.226972,-0.197280,-1.033875));




	cam = new Camera(window);
	/* glfwSetCursorPosCallback(window, ); */  
	
	shader->activate();

	auto myUniformLocation = glGetUniformLocation(shader->get(), "osilator");
	auto incrementorLocation = glGetUniformLocation(shader->get(), "incrementor");

	viewLocation = glGetUniformLocation(shader->get(), "view");
	modelLocation = glGetUniformLocation(shader->get(), "model");
	projectionLocation = glGetUniformLocation(shader->get(), "projection");
	

	glad_glUniform1f(myUniformLocation, 0);
	glad_glUniform1f(incrementorLocation, 0);

	float a = 0;
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
		a += 0.1;
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		auto heading = simpleHeadingAnimation(0.1 * a);

		heliBodyNode->position = glm::vec3(heading.x, 0, heading.z);
		/* heliBodyNode->rotation = glm::vec3(0, a, 0); */
		/* heliTailRotorNode->rotation = glm::vec3(-10*a, 0, 0); */
		/* heliMainRotorNode->rotation = glm::vec3(0, 20*a, 0); */

		heliBodyNode->rotation = glm::vec3(heading.pitch, heading.yaw, heading.roll);
		heliTailRotorNode->rotation = glm::vec3(-10*a, 0, 0);
		heliMainRotorNode->rotation = glm::vec3(0, 20*a, 0);

		glad_glUniform1f(incrementorLocation, a);
		/* glad_glUniformMatrix4fv(modelLocation, 1, GL_FALSE, cam->getModel()); */

        // Draw your scene here
		std::cout << glm::to_string(heliBodyNode->rotation) << std::endl;

		updateSceneNode(rootNode, glm::mat4(1));
		drawSceneNode(rootNode, glm::mat4(1)); 

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
