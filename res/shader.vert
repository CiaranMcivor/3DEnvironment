#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normals;


varying vec2 texCoord0;
varying vec3 normalsPass;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position*5.0f, 1.0); //transform contains MVP
	texCoord0 = texCoord;
	normalsPass = normals;
}