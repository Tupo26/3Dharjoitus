#pragma once
#include "Shader.h"

class ShaderFactory {
public:
	ShaderFactory();
	~ShaderFactory();
	Shader * CreateShader(char name, int ID);
};