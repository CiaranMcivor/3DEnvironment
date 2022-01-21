#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;


uniform mat4 model;

out vec2 texCoord;
out vec3 position;

void main()
{
    position = vec3(model * vec4(aPos, 1.0));
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    texCoord = aTexCoords;
}  