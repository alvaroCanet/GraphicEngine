#include <GLFW/glfw3.h>
#include "ESAT\core\Window.h"


namespace ESAT {
namespace core {

	Window::Window() {}
	
	int Window::Init(int param1,int param2)
	{
		glfwInit();
		//glfwGetVideoMode(mode);
		if(Window::window_ = glfwCreateWindow(param1, param2, "Hello World",NULL, NULL))
		{return 0;}
		 return 1;
	}
	
	void Window::MakeContext(){
		
		/* Make the window's context current */
		glfwMakeContextCurrent(window_);
	}
	
	
	bool Window::WindowsExist(){

		if(!glfwWindowShouldClose(window_)) return true;
		else return false;
	}
      
	void Window::SwapBuffers(){
	 /* Swap front and back buffers */
        glfwSwapBuffers(window_);

	}

    void Window::ProcessEvents(){
	/* Poll for and process events */
        glfwPollEvents();	
	}
   

	void Window::FinishWindow(){

      glfwTerminate();
	
	}
    

}  // core
}  // ESAT
