#version 330 core
layout (location = 0) in int id;

uniform mat4 MVP;
uniform mat4 TransForms[31];

void main() {
  vec4 position = TransForms[id] * vec4(0.0, 0.0, 0.0, 1.0);
  // vec4 position = vec4(pos, 1.0);
  gl_Position = MVP * position;
}