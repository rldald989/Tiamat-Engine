#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec2 shape_position_a;

uniform float threshold;

float SDF(vec2 position)
{
	return distance(position, TexCoord) - threshold;
}

float sdBox( in vec2 position)
{
    vec2 d = abs(position)-TexCoord;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float Union(float a, float b)
{
	const float k = .1;
	float h = max(k - abs(a - b), 0.0) / k;
	return min(a, b) - h * h * k * (1.0 / 4.0);
}

vec3 lerp(vec3 a, vec3 b, float t){
	return a + (b - a) * t;
}

vec3 ColorUnion(float a, float b, vec3 col_a, vec3 col_b, float amount)
{
	return lerp(max(col_a, a), max(col_b, b), a - b * (amount) );
}

void main() {
   //vec4 tex = texture(ourTexture, vec2(TexCoord.x, TexCoord.y));

   float shape_a = SDF(shape_position_a);
   vec2 shape_position_b = vec2(.5, .5);
   float shape_b = sdBox(shape_position_a);

   vec3 col;

   if(Union(shape_a, shape_b) < 0)
   {
		col = ColorUnion(shape_a, shape_b, vec3(1, 0, 0), vec3(0, 1, 0), 1);
   }
   else{
		col = vec3(0);
		}

   FragColor = vec4(col,1.0);
}