#version 330 core

/*Singed Distance function sourced partially from https://iquilezles.org/www/articles/distfunctions/distfunctions.htm
Raymarching inspired by The Art of Codes tutorial series https://www.youtube.com/watch?v=PGtv-dBi2wE&t=503s
*/



uniform vec2 resolution;
uniform vec3 camera;
uniform float time;
uniform vec3 lightColour;
out vec4 fragColour;

int maxSteps = 300;
int maxDistance = 100;
float surfaceDistance = 0.01f;


float signedDistanceSphere( vec3 point, vec4 sphereDimensions )
{
    return length(point - sphereDimensions.xyz)-sphereDimensions.w;
}

float getDistance(vec3 point)
{
    float sphere = signedDistanceSphere(point,vec4(1,1,5,1));
    float dist = min(sphere,point.y);
    return dist;
}

vec3 getNormals(vec3 point)
{
    float dist = getDistance(point);
    vec2 e = vec2(0.01,0);
    
    vec3 normal = dist - vec3(getDistance(point-e.xyy),getDistance(point - e.yxy),getDistance(point - e.yyx));
    return normalize(normal);
}

vec3 getLight(vec3 point, vec3 cameraDirection)
{
// Generate light position, any vec3 position
    vec3 lightPosition = vec3(0,6,3);
    lightPosition.xz += vec2(sin(time*2),cos(time*2));          //this rotates the light on the y axis
    vec3 lightDirection = normalize(lightPosition - point);     
    vec3 normals = getNormals(point);

    // Ambient light 
    float ambientIntensity = 0.1;
    vec3 ambient = ambientIntensity * vec3(1,0,1);
    //Diffuse
    float diff = clamp(dot(normals,lightDirection),0,1);            //Dot prodcut of normals and light direction
    vec3 diffuse = vec3(diff);

    vec3 reflectDir = reflect(-lightDirection, normals);
    float spec = pow(max(dot(cameraDirection, reflectDir), 0.0), 32);
    float specularIntensity = 0.9;
    vec3 specular = specularIntensity * spec * vec3(1,1,1);

    float dotDiffuse = dot(lightDirection, normals); // project light direction to surface normal
    float dotSpec = dot(reflectDir, -cameraDirection); // project light reflection direction to direction to camera
    vec3 result = vec3(0);

    if (dotDiffuse > 0) { //  can see the diffuse
        result += diffuse * dotDiffuse;
    }
    if (dotSpec > 0) { //  can see the specular
        result += specular * pow(dotSpec, 2);
    }
    result *= vec3(1,1,1); // influence of color of the light
    return result + ambient;
}

float rayMarch(vec3 rayOrigin, vec3 rayDirection) {

	float distanceOrigin=0.;
    
    //Ray marching loop
    for(int i=0; i<maxSteps; i++) 
    {
    	vec3 point = rayOrigin + rayDirection*distanceOrigin;               // Point to sample from
        float distanceSphere = getDistance(point);                          // find the nearest point of an object
        distanceOrigin += distanceSphere;
        if(distanceOrigin > maxDistance || distanceSphere < surfaceDistance) break;
    }
    
    return distanceOrigin;
}
    
void main()
{
    //UV grid to draw onto
    vec2 uv = (gl_FragCoord.xy- 0.5*resolution.xy)/resolution.y;

    //Camera Position and facing direction
    vec3 rayOrigin = vec3(0, 1, 0);
    vec3 rayDirection = normalize(vec3(uv.x, uv.y, 1));

    float dist = rayMarch(rayOrigin, rayDirection);
    vec3 point = rayOrigin + rayDirection * dist;

    //vec3 ambientColour = vec3(0.1, 0.1, 0.1);

    vec3 colour = vec3(0);
    //colour +=ambientColour;
    colour += getLight(point,rayDirection) * vec3(0,1,0);
    fragColour = vec4(colour,1.0);
}
