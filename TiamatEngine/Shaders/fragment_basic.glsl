#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
   vec4 tex = texture(ourTexture, TexCoord);
   FragColor = vec4(tex.rgb * color, tex.a);
}