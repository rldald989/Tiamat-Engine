#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 2) in vec2 tex_coords;

out vec2 TexCoord;

void main() {
  gl_Position = vec4(vertex_position, 1.0);
  TexCoord = tex_coords;
}