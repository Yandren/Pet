#include "CPlayerInputMapping.h"
#include <map>
#include "glfw\include\GLFW\glfw3.h"

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

const std::map<const char *, int> valuesToCharacters(mappingData, mappingData + sizeof(mappingData) / sizeof(mappingData[0]));

