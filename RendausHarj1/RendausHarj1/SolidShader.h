#pragma once
#include "Shader.h"

class SolidShader : public Shader {
public:
	SolidShader(int _id) { ID = _id; }
	SolidShader(){}
	~SolidShader() {}
	void Update() {
		//float dTime = glfwGetTime();
		//int loc = glGetUniformLocation(ID, "time");
		//lProgramUniform1f(ID, loc, dTime);
	}
};