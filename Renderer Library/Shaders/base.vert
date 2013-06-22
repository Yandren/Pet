#version 330 core

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;


out vec4 fragmentColor;

//model view projection matrix
uniform mat4 MVP;

void main()
{
  fragmentColor = vertexColor;
  gl_Position = MVP * vertexPosition_modelspace;
}
