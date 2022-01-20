#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec4 gDiffSpec;
layout (location = 2) out vec3 gNormal;


in vec2 texCoord;
in vec3 position;
in vec3 normal;


uniform sampler2D diffuse;
uniform sampler2D specular;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition = position;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(normal);
    // and the diffuse per-fragment color
    gDiffSpec.rgb = texture(diffuse, texCoord).rgb;
    // store specular intensity in alpha component
    gDiffSpec.a = texture(specular, texCoord).r;
}