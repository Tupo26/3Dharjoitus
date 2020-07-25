#include "Cube.h"


Cube::Cube() {
	v_size = 72;
	for (int i = 1; i < 72; i = i + 3) {
		vertices[i] = vertices[i] * 3;
	}
}


Cube::~Cube() {

}

GLfloat * Cube::getVertices() {
	return vertices;
}

GLfloat * Cube::getColors() {
	return colors;

}

GLfloat * Cube::getNormals() {
	return normals;

}
