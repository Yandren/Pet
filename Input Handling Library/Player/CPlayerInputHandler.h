#ifndef __CPLAYERINPUTHANDLER_H
#define __CPLAYERINPUTHANDLER_H

#include "IInputHandler.h"
#include <map>
#include <string>
#include <queue>


/************************************
*
* Forward Declarations
*
*************************************/
struct GLFWwindow;

/************************************
*
* Callbacks
*
*************************************/

/************************************
*
* Structs
*
*************************************/

/************************************
*
* Classes
*
*************************************/

class CPlayerInputHandler : public IInputHandler
{
public:
  //Constructors/Destructors
  CPlayerInputHandler(){}
  CPlayerInputHandler(GLFWwindow* window);
  virtual ~CPlayerInputHandler(){};

  //methods
  bool init(tinyxml2::XMLNode * node, CGameStateManager * man);
  bool processInput(GLFWwindow* window, SInput_t * input, std::vector<IInputContext *> contexts);
  static void keyboardKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void mousePressed(GLFWwindow* window, int button, int action, int mods); 
   //members
  protected:
  private:
  //methods
  //members
  GLFWwindow* mWindow; 

};
#endif