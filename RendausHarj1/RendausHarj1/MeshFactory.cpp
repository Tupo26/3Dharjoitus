#include "MeshFactory.h"
#include "Mesh.h"
#include "Plane.h"
#include "Cube.h"

MeshFactory::MeshFactory() {

}

MeshFactory::~MeshFactory(){}

Plane * MeshFactory::CreateMesh(char t) {
	Plane * m;

	switch (t)
	{
	case 'p':
		m = new Plane();
		break;
	default:
		m = new Plane();
		break;
	}

	return m;
}