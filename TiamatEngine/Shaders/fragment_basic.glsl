#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
   vec4 tex = texture(ourTexture, vec2(-TexCoord.x, TexCoord.y));
   FragColor = vec4(tex.rgb * color, 1.0);
}