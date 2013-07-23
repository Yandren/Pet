#include "CPlayerInputHandler.h"
#include "glfw\include\GLFW\glfw3.h"
#include "Component System\CComponentMessage.h"
#include "Component System\ComponentStructs.h"
#include "CObjectManager.h"
#include "Globals.h"
#include <functional>





CPlayerInputHandler::CPlayerInputHandler(GLFWwindow* window)
  : mWindow(window)
{
  //tell GLFW that we want callbacks to be routed through this function
  glfwSetKeyCallback( mWindow, CPlayerInputHandler::keyboardKeyPressed);

}

bool
  CPlayerInputHandler::processInput(GLFWwindow* window, SInput_t * input, std::vector<IInputContext *> contexts)
{
  if(window != mWindow)
  {
    CLog::Get()->Write(LOG_ERROR, "Handling input for window we shouldn't be");
    return false;
  }
  for(int i = 0; i < contexts.size(); i++)
  {
    IInputContext * activeContext = contexts.front();
    if(!activeContext->containsKey(input))
    {
      break;
    }
    //get the mapping for our input
    activeContext->mInputMappings.at(input)->evoke();

  }//end for loop
  return true;
}

void
  CPlayerInputHandler::keyboardKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  SKeyboardKey_t * keyPress = new SKeyboardKey_t(key);
  mIncomingInput.push(keyPress);
}


//TODO - we are using GLFW in place of platform-dependent input handling.
//someday I might get bored enough to go implement all the specifics


// Initializing the static values of our char->int value key mapping
const static std::pair<const char *, int> mappingData[] =
{
  std::make_pair("Comma", GLFW_KEY_COMMA),
  std::make_pair("Dash", GLFW_KEY_MINUS),
  std::make_pair("Period", GLFW_KEY_PERIOD),
  std::make_pair("0", GLFW_KEY_0),
  std::make_pair("1", GLFW_KEY_1),
  std::make_pair("2", GLFW_KEY_2),
  std::make_pair("3", GLFW_KEY_3),
  std::make_pair("4", GLFW_KEY_4),
  std::make_pair("5", GLFW_KEY_5),
  std::make_pair("6", GLFW_KEY_6),
  std::make_pair("7", GLFW_KEY_7),
  std::make_pair("8", GLFW_KEY_8),
  std::make_pair("9", GLFW_KEY_9),
  std::make_pair("A", GLFW_KEY_A),
  std::make_pair("B", GLFW_KEY_B),
  std::make_pair("D", GLFW_KEY_D),
  std::make_pair("W", GLFW_KEY_W),
  std::make_pair("S", GLFW_KEY_S),
  std::make_pair("RightArrow", GLFW_KEY_RIGHT),
  std::make_pair("LeftArrow", GLFW_KEY_LEFT),
  std::make_pair("UpArrow", GLFW_KEY_UP),
  std::make_pair("DownArrow", GLFW_KEY_DOWN)
};

//TODO: either use a bimap or some sort of template magic to initalize this
const static std::pair< int, const char *> mappingReverse[] =
{
  std::make_pair(mappingData[0].second, mappingData[0].first),
  std::make_pair(mappingData[1].second, mappingData[1].first),
  std::make_pair(mappingData[2].second, mappingData[2].first),
  std::make_pair(mappingData[3].second, mappingData[3].first),
  std::make_pair(mappingData[4].second, mappingData[4].first),
  std::make_pair(mappingData[5].second, mappingData[5].first),
  std::make_pair(mappingData[6].second, mappingData[6].first),
  std::make_pair(mappingData[7].second, mappingData[7].first),
  std::make_pair(mappingData[8].second, mappingData[8].first),
  std::make_pair(mappingData[9].second, mappingData[9].first),
  std::make_pair(mappingData[10].second, mappingData[10].first),
  std::make_pair(mappingData[11].second, mappingData[11].first),
  std::make_pair(mappingData[12].second, mappingData[12].first),
  std::make_pair(mappingData[13].second, mappingData[13].first),
  std::make_pair(mappingData[14].second, mappingData[14].first),
  std::make_pair(mappingData[15].second, mappingData[15].first),
  std::make_pair(mappingData[16].second, mappingData[16].first),
  std::make_pair(mappingData[17].second, mappingData[17].first),
  std::make_pair(mappingData[18].second, mappingData[18].first),
  std::make_pair(mappingData[19].second, mappingData[19].first),
  std::make_pair(mappingData[20].second, mappingData[20].first),
  std::make_pair(mappingData[21].second, mappingData[21].first)
};

const std::map<const char *, int> SKeyboardKey_t::charactersToValues(mappingData, mappingData + sizeof(mappingData) / sizeof(mappingData[0]));

const std::map<int, const char *> SKeyboardKey_t::valuesToCharacters(mappingReverse, mappingReverse + sizeof(mappingReverse) / sizeof(mappingReverse[0]));
