#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 position;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDiffSpec;

struct Light {
    vec3 Position;
    vec3 Color;
    
    float Linear;
    float Quadratic;
};
uniform Light light;
uniform vec3 viewPos;

void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, texCoord).rgb;
    vec3 Normal = texture(gNormal, texCoord).rgb;
    vec3 Diffuse = texture(gDiffSpec, texCoord).rgb;
    float Specular = texture(gDiffSpec, texCoord).a;
    
    // then calculate lighting as usual
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component

    // diffuse
    vec3 lightDir = normalize(light.Position - position);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.Color;
    // specular
    vec3 viewDir  = normalize(viewPos - position);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
    vec3 specular = light.Color * spec * Specular;
    // attenuation
    float distance = length(light.Position - position);
    float attenuation = 1.0 / (1.0 + light.Linear * distance + light.Quadratic * distance * distance);
    diffuse *= attenuation;
    specular *= attenuation;


    lighting += diffuse + specular;        
    FragColor = vec4(lighting, 1.0);
}