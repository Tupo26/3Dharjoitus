#include "Plane.h"



Plane::~Plane() {
	
}

GLfloat * Plane::getVertices() {
	return vertices;
}

GLfloat * Plane::getColors() {
	return colors;

}

GLfloat * Plane::getNormals() {
	return normals;

}