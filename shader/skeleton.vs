#version 330 core
layout (location = 0) in int id;
layout (location = 1) in vec3 pos;

uniform mat4 MVP;
uniform mat4 rootTransform;
uniform mat4 childTransform;

void main() {
  vec4 position = vec4(pos, 1.0);
  if (id == 0)
  {
	  position = rootTransform * position;
  }
  if (id == 1)
  {
	  position = rootTransform * childTransform * position;
  }
  gl_Position = MVP * position;
}