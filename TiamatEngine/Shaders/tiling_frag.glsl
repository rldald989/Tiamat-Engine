#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec2 tiling;
uniform vec2 texture_position;

void main() {
   vec4 tex = texture(ourTexture, TexCoord * tiling + texture_position);
   FragColor = vec4(tex.rgb * color, tex.a);
}