#version 330 core
layout (location = 0) in int id;
layout (location = 1) in vec3 pos;

uniform mat4 MVP;
uniform mat4 TransForms[31];

void main() {
  vec4 position = TransForms[int(floor(id + 0.5))] * vec4(pos, 1.0);
  // vec4 position = vec4(pos, 1.0);
  gl_Position = MVP * position;
}