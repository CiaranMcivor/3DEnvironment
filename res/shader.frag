#version 120

varying vec2 texCoord0;
varying vec3 normalsPass;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0);
}
