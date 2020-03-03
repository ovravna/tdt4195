#ifndef CAMERA
#define CAMERA

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtx/string_cast.hpp"
#include <cstdio>
#include <GLFW/glfw3.h>
/* #include <glad/glad.h> */

class Camera {

	private:
		  const float cameraSpeed = 0.05f; // adjust accordingly
          glm::mat4x4 view;
          glm::mat4x4 model;
          glm::mat4x4 projection;
          float speed;
          float rotation = 0;

          glm::vec3 up;
          glm::vec3 right;

          glm::vec3 front;
          glm::vec3 position;

          int windowHeight, windowWidth;
          GLFWwindow *window;

	public:
		Camera(GLFWwindow* window) {
			this->window = window;


			speed = 0.01;

			glfwGetWindowSize(window, &windowWidth, &windowHeight);

			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);


			position = glm::vec3(0, 0, -3);
			front = glm::vec3(0, 0, 1);

			model = glm::mat4(1.0f);
			/* model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); */ 

			view = glm::mat4x4(1.0);
			/* view = glm::translate(view, glm::vec3(0, 0, -3)); */
			view = glm::lookAt(position, position + front, up);

		
			/* projection = glm::mat4x4(1.0); */
			projection = glm::perspective(glm::radians(45.0f), float(windowWidth) / float(windowHeight), 0.1f, 100.0f);
	

			/* view *= glm::lookAt(position, front, up); */


		};

		float * getView() { return glm::value_ptr(view); };
		float * getModel() { return glm::value_ptr(model); };
		float * getProjection() { return glm::value_ptr(projection); };

		void tick() {
				/* model = glm::rotate(model, glm::radians(10.0f) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)); */ 
			view = glm::lookAt(position, position + front, up);
		}
		void handleKeyboardInput()
		{
			tick();

			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				front += glm::normalize(glm::cross(front, up)) * cameraSpeed;
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				front -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
			}
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				auto right = glm::normalize(glm::cross(front, up));
				front -= glm::normalize(glm::cross(front, right)) * cameraSpeed;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				auto right = glm::normalize(glm::cross(front, up));
				front +=  glm::normalize(glm::cross(front, right))* cameraSpeed;
			}

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				position += cameraSpeed * front;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				position -= cameraSpeed * front;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				front += glm::normalize(glm::cross(front, up)) * cameraSpeed;
			}
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				front -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
			}
			/* else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) */
			/* { */
			/* 	/1* auto tempMat = glm::mat4x4(1.0); *1/ */
			/* 	/1* tempMat[1][3] = -speed; *1/ */
			/* 	/1* viewMatrix *= tempMat; *1/ */
			/* 	rotation += 0.1; */
			/* 	float r = 1; */ 
			/* 	position = glm::vec3(sinf(rotation) * r, 0, cosf(rotation) * r); */
				
			/* 	std::printf("%s\n", glm::to_string(position).c_str()); */
				

			/* 	auto mat = glm::lookAt(position, front, up); */
			/* 	view = mat; */
			/* } */

		}
		
};


#endif
