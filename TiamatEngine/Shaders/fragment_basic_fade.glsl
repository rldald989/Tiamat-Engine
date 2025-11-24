#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
in vec3 v_position;

uniform vec3 color;
uniform sampler2D ourTexture;
uniform float fade_time;

void main() {
   vec4 tex = texture(ourTexture, TexCoord);

   float bars;

   if(sin(TexCoord.y * 128) > .8){
	bars = .2;
   }
   else{
	bars = 1;
   }

   FragColor = vec4(tex.rgb * color, tex.a * fade_time * bars);
}