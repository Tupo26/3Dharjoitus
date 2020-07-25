#pragma once

#include <GLFW/glfw3.h>
#include <vector>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
struct vertex{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat color[3];
	vertex(GLfloat _x, GLfloat _y, GLfloat _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	void setColor(GLfloat r, GLfloat g, GLfloat b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
};
struct line {
	vec3 p0;
	vec3 p1;
	vec3 d;
	line(vec3 v0, vec3 v1) {
		p0 = v0;
		p1 = v1;
		d = p1 - p0;
	}
	void UpdateLine(vec3 v0, vec3 v1) {
		p0 = v0;
		p1 = v1;
		d = p1 - p0;
	}
};

class Mesh {
public:

	int v_size;

	vector<line> linelist;
	vector<vertex> vertexlist;

	virtual GLfloat * getVertices() = 0;
	virtual GLfloat * getColors() = 0;
	virtual GLfloat * getNormals() = 0;
	virtual vec3 getLineStart() = 0;
	virtual vec3 getLineEnd() = 0;
	virtual void RotateY(float a) = 0;
	virtual void RotateX(float a) = 0;
	virtual void RotateZ(float a) = 0;

	vec3 CalculateNormal(vec3 v1, vec3 v2, vec3 v3) {
		vec3 U(v2.x - v1.x, v2.y - v1.y, v2.y - v1.y);
		vec3 V(v3.x - v1.x, v3.y - v1.y, v3.y - v1.y);

		vec3 N(
			U.y * V.z - U.z * V.y, 
			U.z * V.x - U.x * V.z,
			U.x * V.y - U.y * V.x
		);
		return N;
	};

	vec3 RotateVertexY(float a, vec3 v) {
		mat3 rm = mat3(
			cos(a), 0, -sin(a),
			0, 1, 0,
			sin(a), 0, cos(a)
		);

		vec3 rv = v * rm;

		return rv;
	};

	vec3 RotateVertexX(float a, vec3 v) {
		mat3 rm = mat3(
			1, 0, 0,
			0, cos(a), sin(a),
			0, -sin(a), cos(a)
		);

		vec3 rv = v * rm;

		return rv;
	};

	vec3 RotateVertexZ(float a, vec3 v) {
		mat3 rm = mat3(
			cos(a), sin(a), 0,
			-sin(a), cos(a), 0,
			0, 0, 1
		);

		vec3 rv = v * rm;

		return rv;
	};

	void Scale(GLfloat *v, int vs, GLfloat x, GLfloat y, GLfloat z) {
		GLfloat *p = v;
		for (int i = 0; i < vs; i = i + 3) {
			*p = *p * x;
			p++;
			*p = *p * y;
			p++;
			*p = *p * y;
			p++;
		}
	};

	void Translate(GLfloat *v, int vs, GLfloat x, GLfloat y, GLfloat z) {
		GLfloat *p = v;

		for (int i = 0; i < vs; i = i + 3) {
			*p = *p + x;
			p++;
			*p = *p + y;
			p++;
			*p = *p + z;
			p++;
		}
	};
};