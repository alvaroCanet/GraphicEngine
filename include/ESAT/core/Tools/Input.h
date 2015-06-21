#ifndef _INPUT_H__
#define _INPUT_H__

#include "GLFW/glfw3.h" 
#include <ESAT/core/GPU.h>

namespace ESAT {
namespace core {

	class Input {
	
	protected:
		
		
	public:
		
		static void CheckKey(GLFWwindow * window,int key,int code, int action ,int mode)
		{
			if (action == GLFW_PRESS)
			{
				if(key == GLFW_KEY_F5)
				{
					Reload();
					//glfwTerminate();
				}
			}
		}
		static void cursorPosFun(GLFWwindow* window, double x, double y)
		{
			TwEventMousePosGLFW(x, y);
		}

		 static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		 {
			TwEventMouseButtonGLFW(button, action);
		 }

		 static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		 {
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		 }


		static void Reload()
		{
			 
		}

		void Init(GLFWwindow * window)
		{
			glfwSetKeyCallback(window,CheckKey);
			glfwSetMouseButtonCallback(window,mouseButtonCallback);
			glfwSetCursorPosCallback(window,cursorPosFun);
			glfwSetKeyCallback(window, key_callback);
		}

		Input(){};
		~Input(){};
		
		void Update();
	private:

	};
}
}
#endif 