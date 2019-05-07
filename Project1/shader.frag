#version 150


varying vec2 varying_texcoord;
uniform sampler2D txtr;

uniform bool horizontal;
uniform float weight[5] = float[] (0.527027, 0.1945946, 0.1216216, 0.054054, 0.016216);

out vec4 outColor;
void main()
{	
	outColor = texture2D()
} 