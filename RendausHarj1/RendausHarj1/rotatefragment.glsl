// simple fragment shader

// 'time' contains seconds since the program was linked.
#version 330 core

uniform float time;
out vec3 color;

void main()
{
	//gl_FragColor = gl_Color;
	color = vec3(0,1,0);
}
