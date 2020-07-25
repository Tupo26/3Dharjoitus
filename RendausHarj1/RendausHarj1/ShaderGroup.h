#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>

class ShaderGroup
{
public:
	ShaderGroup();
	~ShaderGroup();
	GLuint NewShader(char name, char* v, char* f, char* g);
	
	void AttachMesh(Mesh* m, int ID);

	vector<Shader*> shaders;
	int count = 0;

	int GetShaderID(int i);
	void UpdateShader(int i);
	Mesh* GetMeshes(int i, int j);
	int GetMeshCount(int i);

private:

};