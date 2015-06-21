#ifndef __WINDOW__H_ //1
#define __WINDOW__H_

#include <GLFW/glfw3.h>

namespace ESAT {
namespace core {

  class Window
  {
  public:
	  GLFWwindow* window_;
	  GLFWmonitor* mode;
	  Window();
	  int Init(int param1,int param2);
	  void MakeContext();
	  bool WindowsExist();
	  void FinishWindow();
	  void SwapBuffers();
	  void ProcessEvents();

  private:


  };


}  // core
}  // ESAT

#endif // INCLUDE_ESAT_CLOCK_H_