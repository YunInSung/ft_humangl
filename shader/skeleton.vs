#version 330 core
layout (location = 0) in float id;
layout (location = 1) in vec3 pos;

uniform mat4 MVP;
uniform mat4 rootTransform;
uniform mat4 childTransform;

bool equalCheck(float a, float b)
{
  if (abs(a - b) < 0.0001)
		return true;
	return false;
}

void main() {
  vec4 position = vec4(pos, 1.0);
  if (equalCheck(id, 0.0f))
  {
	  position = rootTransform * position;
  }
  else if (equalCheck(id, 1.0f))
  {
    position = rootTransform * childTransform * position;
  }
  gl_Position = MVP * position;
}