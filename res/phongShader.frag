#version 330 core
out vec4 fragColor;

in vec3 normals;  
in vec3 position;  
  
uniform vec3 lightPosition; 
uniform vec3 cameraPosition; 
uniform vec3 lightColour;
uniform vec3 modelColour;

void main()
{
    // Ambient Lighting
    float ambientIntensity = 0.1;
    vec3 ambient = ambientIntensity * lightColour;
  	
    // Diffuse Lighting 
    vec3 normal = normalize(normals);
    vec3 lightDirection = normalize(lightPosition - position);

    float diff = max(dot(normal, lightDirection), 0.0); //Dot prodcut of normals and light direction
    vec3 diffuse = diff * lightColour;                  // Multiply by light colour
    
    // Specular Lighting

    vec3 cameraDirection = normalize(cameraPosition - position);
    vec3 reflectDir = reflect(-lightDirection, normal);                 // Reflection away from light source

    vec3 halfwayDir = normalize(lightDirection + cameraDirection);
    
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    //float spec = pow(max(dot(cameraDirection, reflectDir), 0.0), 32);
    float specularIntensity = 0.5;
    vec3 specular = specularIntensity * spec * lightColour;

        
    vec3 result = (ambient + diffuse + specular) * modelColour; //Lighting calculation multiplyed by modelColour result is a yellow sphere
    fragColor = vec4(result, 1.0);
} 