#pragma once
#include<iostream>
#include "Mesh.h"

class Plane{
public:
	int v_size;

	vector<line> linelist;
	vector<vertex> vertexlist;

	GLfloat vertices[18] = { -1, 0, 1,
					1, 0, 1,
				   1, 0, -1,
					1, 0, -1,
				   -1, 0, -1,
					-1, 0, 1 };

	GLfloat colors[18] = { 1, 0, 0,
					1, 0, 0,
				   1, 0, 0,
				   0, 1, 0,
					0, 1, 0,
				   0, 1, 0 };

	GLfloat normals[18] = {0,0,0,
							0,0,0,
							0,0,0, 
							0,0,0, 
							0,0,0, 
							0,0,0 };

				   

	Plane() {
		v_size = 18;
		//First triangle's edges
		line e0(vec3(vertices[0], vertices[1], vertices[2]), vec3(vertices[3], vertices[4], vertices[5]));
		linelist.push_back(e0);
		line e1(vec3(vertices[3], vertices[4], vertices[5]), vec3(vertices[6], vertices[7], vertices[8]));
		linelist.push_back(e1);

		//Second triangle's edges
		line e2(vec3(vertices[9], vertices[10], vertices[11]), vec3(vertices[12], vertices[13], vertices[14]));
		linelist.push_back(e2);
		line e3(vec3(vertices[12], vertices[13], vertices[14]), vec3(vertices[15], vertices[16], vertices[17]));
		linelist.push_back(e3);

		//Calculating normals
		for (int i = 0; i < v_size; i = i + 9) {
			vec3 v1(vertices[i], vertices[i+1], vertices[i+2]);
			vec3 v2(vertices[i+3], vertices[i+4], vertices[i+5]);
			vec3 v3(vertices[i+6], vertices[i+7], vertices[i+8]);
			vec3 n1 = CalculateNormal(v1, v2, v3);
			//vec3 n1 = normalize(n);
			//cout << "Normalisoitu: " << n1.x << endl;
			normals[i] = n1.x;
			normals[i+1] = n1.y;
			normals[i+2] = n1.z;
			normals[i+3] = n1.x;
			normals[i+4] = n1.y;
			normals[i+5] = n1.z;
			normals[i+6] = n1.x;
			normals[i+7] = n1.y;
			normals[i+8] = n1.z;
		}
	};
	Plane(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
		v_size = 18;
		vertices[0] = v0.x; vertices[1] = v0.y; vertices[2] = v0.z;
		vertices[3] = v2.x; vertices[4] = v2.y; vertices[5] = v2.z;
		vertices[6] = v3.x; vertices[7] = v3.y; vertices[8] = v3.z;
		vertices[9] = v0.x; vertices[10] = v0.y; vertices[11] = v0.z;
		vertices[12] = v2.x; vertices[13] = v2.y; vertices[14] = v2.z;
		vertices[15] = v1.x; vertices[16] = v1.y; vertices[17] = v1.z;
	};
	~Plane();

	GLfloat * getVertices();
	GLfloat * getColors();
	GLfloat * getNormals();

	vec3 getNormal1() {
		vec3 norm(normals[0], normals[1], normals[2]);
		return norm;
	}

	

	void RotateY(float a) {
		for (int i = 0; i < v_size; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexY(a, v);
			vertices[i] = r.x;
			vertices[i + 1] = r.y;
			vertices[i + 2] = r.z;
		}
	};

	void RotateX(float a) {
		for (int i = 0; i < v_size; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexX(a, v);
			vertices[i] = r.x;
			vertices[i + 1] = r.y;
			vertices[i + 2] = r.z;
		}
	};

	void RotateZ(float a) {
		for (int i = 0; i < v_size; i = i + 3) {
			vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
			vec3 r = RotateVertexZ(a, v);
			vertices[i] = r.x;
			vertices[i + 1] = r.y;
			vertices[i + 2] = r.z;
		}
	};
	
	void UpdateEdges() {
		linelist[0].UpdateLine(vec3(vertices[0], vertices[1], vertices[2]), vec3(vertices[3], vertices[4], vertices[5]));
		linelist[1].UpdateLine(vec3(vertices[3], vertices[4], vertices[5]), vec3(vertices[6], vertices[7], vertices[8]));
		linelist[2].UpdateLine(vec3(vertices[9], vertices[10], vertices[11]), vec3(vertices[12], vertices[13], vertices[14]));
		linelist[3].UpdateLine(vec3(vertices[12], vertices[13], vertices[14]), vec3(vertices[15], vertices[16], vertices[17]));
	}

	vec3 getLineStart(int i) {
		return linelist[i].p0;
	}

	vec3 getLineEnd(int i) {
		return linelist[i].p1;
	}

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

