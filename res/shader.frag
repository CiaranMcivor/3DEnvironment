#version 330 core

    out vec4 FragColor;


uniform vec2 resolution;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){


	vec3 color = vec3(1,1,1);

	FragColor = vec4( color, 1.0 );
}
