#pragma once

//#include <GL/glew.h>

#include <vector>
using namespace std;
#include "Mesh.h"

class Shader
{
public:
	Shader();
	~Shader();
	void AddMesh(Mesh* m);
	Mesh* GetMesh(int i);
	virtual void Update();
	GLuint ID;
	int count = 0;
	vector<Mesh*> meshes;


private:

};

Shader::Shader(){}

Shader::~Shader(){}

void Shader::AddMesh(Mesh* m) {
	meshes.push_back(m);
	count++;
}

Mesh* Shader::GetMesh(int i) {
	return meshes[i];
}