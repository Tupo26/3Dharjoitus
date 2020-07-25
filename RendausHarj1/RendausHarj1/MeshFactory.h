#pragma once
#include "Mesh.h"
#include "Plane.h"
#include "Cube.h"

class MeshFactory {
public:
	MeshFactory();
	 ~MeshFactory();
	 Plane * CreateMesh(char t);
};