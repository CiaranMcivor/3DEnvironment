//Version number
#version 400
in vec2 TexCoords;

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
//Unfrom variable
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;

uniform sampler2D diffuse;
 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	vec4 color;
	color = texture2D(diffuse, TexCoords);
    fragcolor = color;
}