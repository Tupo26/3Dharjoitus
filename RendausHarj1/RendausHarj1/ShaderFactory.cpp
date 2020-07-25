#include "ShaderFactory.h"
#include "SolidShader.h"

ShaderFactory::ShaderFactory() {

}

ShaderFactory::~ShaderFactory() {

}

Shader* ShaderFactory::CreateShader(char name, int ID) {
	Shader* s;
	switch (name)
	{
	case 's':
		s = new SolidShader(ID);
		break;
	default:
		s = new SolidShader(ID);
		break;
	}

	return s;
}