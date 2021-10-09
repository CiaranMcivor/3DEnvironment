#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 normal;

out vec3 normals;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    position = vec3(model * vec4(pos, 1.0));
    normals = mat3(transpose(inverse(model))) * normal;  
    gl_Position = projection * view * vec4(position, 1.0);
}