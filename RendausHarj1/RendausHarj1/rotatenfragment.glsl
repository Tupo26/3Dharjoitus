// simple fragment shader

// 'time' contains seconds since the program was linked.
#version 330 core

uniform float time;
out vec4 color;

void main()
{
	//gl_FragColor = gl_Color;
	color = vec4(0,	0,1,0.1);
}
