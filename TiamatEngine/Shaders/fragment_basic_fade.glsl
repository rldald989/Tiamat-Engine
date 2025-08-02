#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float fade_time;

void main() {
   vec4 tex = texture(ourTexture, vec2(TexCoord.x, TexCoord.y));

   float bars;

   if(sin(TexCoord.y * 128) > .8){
	bars = .2;
   }
   else{
	bars = 1;
   }

   FragColor = vec4(tex.rgb * color, tex.a * fade_time * bars);
}