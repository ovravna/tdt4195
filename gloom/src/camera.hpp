#ifndef CAMERA
#define CAMERA

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <GLFW/glfw3.h>
/* #include <glad/glad.h> */

class Camera {

	public:
		Camera() {
			viewMatrix = glm::mat4x4(1.0);
			speed = 0.05;

		};
		
		float * getViewMatrix() { return glm::value_ptr(viewMatrix); };

		void handleKeyboardInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				auto tempMat = glm::mat4x4(1.0);
				tempMat[0][3] = speed;

				viewMatrix *= tempMat;

			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				auto tempMat = glm::mat4x4(1.0);
				tempMat[0][3] = -speed;

				viewMatrix *= tempMat;
			}
			else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				auto tempMat = glm::mat4x4(1.0);
				tempMat[1][3] = speed;

				viewMatrix *= tempMat;
			}
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				auto tempMat = glm::mat4x4(1.0);
				tempMat[1][3] = -speed;

				viewMatrix *= tempMat;
			}
		}

	private:

		glm::mat4x4 viewMatrix;
		float speed;
};


#endif
