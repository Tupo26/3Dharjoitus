#include "ShaderGroup.h"
#include "ShaderFactory.h"
#include "common/shader.hpp"

ShaderGroup::ShaderGroup() {
}

ShaderGroup::~ShaderGroup() {

}

GLuint ShaderGroup::NewShader(char name, char* v, char* f, char*g) {
	ShaderFactory* SF = new ShaderFactory();

	GLuint ID = LoadShaders(v, f);
	Shader* s = SF->CreateShader(name, ID);
	shaders.push_back(s);
	count++;

	return ID;
}

void ShaderGroup::AttachMesh(Mesh* m, int ID) {
	shaders[ID]->AddMesh(m);
}

int ShaderGroup::GetShaderID(int i) {
	int ID = shaders[i]->ID;
	return ID;
}

void ShaderGroup::UpdateShader(int i) {
	shaders[i]->Update();
}

Mesh* ShaderGroup::GetMeshes(int i, int j) {
	return shaders[i]->GetMesh(j);

}

int ShaderGroup::GetMeshCount(int i) {
	return shaders[i]->count;
}