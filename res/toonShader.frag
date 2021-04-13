#version 400
out vec4 FragColor;
in vec3 v_norm;
in vec4 v_pos; 

uniform vec3 fogColor;

uniform vec3 lightDirection;	// Uniform to hold light direction
in vec3 normal;			// intake of normals from vertex shader



void main() 
{
	float intensity;
	vec4 colour;

	intensity = dot(lightDirection, normal);

	if (intensity > 0.95)
	{
		colour = vec4(1.0,0.5,0.5,1.0);
	}

	else if (intensity > 0.5)
	{
		colour = vec4(0.6,0.3,0.3,1.0);
	}

	else if	(intensity > 0.25)
	{
		colour = vec4(0.4,0.2,0.2,1.0);
	}

	else
	{
		colour = vec4(0.2,0.1,0.1,1.0);
	}


	gl_FragColor = colour;
}
