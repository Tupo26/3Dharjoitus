#pragma once
#include "Mesh.h"

class Cube : public Mesh{
public:
	GLfloat vertices[72] =
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		 1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat colors[72] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	GLfloat normals[72] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	Cube();
	~Cube();

	GLfloat * getVertices();
	GLfloat * getColors();
	GLfloat * getNormals();

	vec3 getLineStart(int i) {
		return vec3(0,0,0);
	}

	vec3 getLineEnd(int i) {
		return vec3(0, 0, 0);
	}

	void RotateY(float a) {
		for (int i = 0; i < 72; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexY(a, v);
			vertices[i] = r.x;
			vertices[i+1] = r.y;
			vertices[i+2] = r.z;
		}
	};

	void RotateX(float a) {
		for (int i = 0; i < 72; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexX(a, v);
			vertices[i] = r.x;
			vertices[i + 1] = r.y;
			vertices[i + 2] = r.z;
		}
	};

	void RotateZ(float a) {
		for (int i = 0; i < 72; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexZ(a, v);
			vertices[i] = r.x;
			vertices[i + 1] = r.y;
			vertices[i + 2] = r.z;
		}
	};
};