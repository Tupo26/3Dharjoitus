#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
using namespace glm;

#include <common/shader.hpp>

#include "Plane.h"
#include "Mesh.h"
#include "Cube.h"
#include "MeshFactory.h"

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return NULL;
	}

	glfwSetKeyCallback(window, controls);

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return window;
}

void DrawPoint(GLfloat points[3]) {
	GLfloat colors[3] = { 1,1,1 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, 1);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawLine(GLfloat points[6]) {
	GLfloat colors[6] = { 1,1,1, 1, 1, 1 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glPointSize(10.0f);
	glDrawArrays(GL_LINES, 0, 2);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawTriangle(GLfloat points[9], int c = 0) {
	
	GLfloat colors[9] = { 1,0,0, 1, 0, 0, 1,0,0 };
	if (c) {
		for (int i = 0; i < 9; i = i + 3) {
			colors[i] = 0;
			colors[i + 1] = 1;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glPointSize(10.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawMesh(Plane * m) {
	GLfloat *v;
	GLfloat *c;
	v = m->getVertices();
	c = m->getColors();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	glColorPointer(3, GL_FLOAT, 0, c);

	/* Send data : 24 vertices */
	glPointSize(10.0f);
	glDrawArrays(GL_TRIANGLES, 0, m->v_size/3);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
void RenderRefraction(vec3 c_points[36], int l, GLuint aboveID, GLuint BelowID) {
	bool lineOverlap = false;
	GLfloat overLapPoint[3] = { 0, 0, 0 };
	for (int i = 0; i < l; i++) {
		GLfloat piste[3] = { c_points[i].x, c_points[i].y, c_points[i].z };
		//DrawPoint(piste);
		for (int j = 0; j < l; j++) {
			if (j != i) {
				if (c_points[i].x == c_points[j].x && c_points[i].y == c_points[j].y && c_points[i].z == c_points[j].z) {
					lineOverlap = true;
					overLapPoint[0] = c_points[i].x;
					overLapPoint[1] = c_points[i].y;
					overLapPoint[2] = c_points[i].z;
				}
			}
		}
	}
	vec3 norm(0, 1, 0);
	if (lineOverlap) {
		//DrawPoint(overLapPoint);

		GLfloat lostPoint[3] = { 0,0,0 };
		//Pikkukolmio
		GLfloat dotproduct = (norm.x * (overLapPoint[0] - c_points[1].x)) + (norm.y * (overLapPoint[1] - c_points[1].y)) + (norm.z * (overLapPoint[2] - c_points[1].x));
		if (dotproduct > 0)
			glUseProgram(aboveID);
		else
			glUseProgram(BelowID);
		GLfloat triangle[9] = { c_points[1].x, c_points[1].y, c_points[1].z, c_points[4].x, c_points[4].y, c_points[4].z, overLapPoint[0], overLapPoint[1],overLapPoint[2] };
		DrawTriangle(triangle, 1);
		if (overLapPoint[0] == c_points[5].x && overLapPoint[1] == c_points[5].y && overLapPoint[2] == c_points[5].z) {
	
			lostPoint[0] = c_points[2].x - c_points[5].x + c_points[3].x;
			lostPoint[1] = c_points[2].y - c_points[5].y + c_points[3].y;
			lostPoint[2] = c_points[2].z - c_points[5].z + c_points[3].z;
			//Loppukolmiot
			if (dotproduct < 0)
				glUseProgram(aboveID);
			else
				glUseProgram(BelowID);
			triangle[0] = c_points[1].x; triangle[1] = c_points[1].y; triangle[2] = c_points[1].z;
			triangle[3] = c_points[4].x; triangle[4] = c_points[4].y; triangle[5] = c_points[4].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle);
			triangle[0] = c_points[2].x; triangle[1] = c_points[2].y; triangle[2] = c_points[2].z;
			triangle[3] = c_points[1].x; triangle[4] = c_points[1].y; triangle[5] = c_points[1].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle, 1);
			triangle[0] = c_points[3].x; triangle[1] = c_points[3].y; triangle[2] = c_points[3].z;
			triangle[3] = c_points[4].x; triangle[4] = c_points[4].y; triangle[5] = c_points[4].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle);
		}
		else {
			lostPoint[0] = c_points[0].x - c_points[2].x + c_points[5].x;
			lostPoint[1] = c_points[0].y - c_points[2].y + c_points[5].y;
			lostPoint[2] = c_points[0].z - c_points[2].z + c_points[5].z;
			//Loppukolmiot
			if (dotproduct < 0)
				glUseProgram(aboveID);
			else
				glUseProgram(BelowID);
			triangle[0] = c_points[1].x; triangle[1] = c_points[1].y; triangle[2] = c_points[1].z;
			triangle[3] = c_points[4].x; triangle[4] = c_points[4].y; triangle[5] = c_points[4].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle);
			triangle[0] = c_points[0].x; triangle[1] = c_points[0].y; triangle[2] = c_points[0].z;
			triangle[3] = c_points[1].x; triangle[4] = c_points[1].y; triangle[5] = c_points[1].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle, 1);
			triangle[0] = c_points[5].x; triangle[1] = c_points[5].y; triangle[2] = c_points[5].z;
			triangle[3] = c_points[4].x; triangle[4] = c_points[4].y; triangle[5] = c_points[4].z;
			triangle[6] = lostPoint[0]; triangle[7] = lostPoint[1]; triangle[8] = lostPoint[2];
			DrawTriangle(triangle);
		}

		//DrawPoint(lostPoint);
		
	}
	else {
		Plane *plnpoint;
		GLfloat dotproduct = (norm.x * (c_points[0].x - c_points[1].x)) + (norm.y * (c_points[0].y - c_points[1].y)) + (norm.z * (c_points[0].z - c_points[1].z));

		if (dotproduct > 0)
			glUseProgram(aboveID);
		else
			glUseProgram(BelowID);

		Plane pln1 = Plane(vec3(c_points[0].x, c_points[0].y, c_points[0].z),
			vec3(c_points[1].x, c_points[1].y, c_points[1].z),
			vec3(c_points[4].x, c_points[4].y, c_points[4].z),
			vec3(c_points[5].x, c_points[5].y, c_points[5].z));
		plnpoint = &pln1;
		DrawMesh(plnpoint);

		if (dotproduct < 0)
			glUseProgram(aboveID);
		else
			glUseProgram(BelowID);

		Plane pln2 = Plane(vec3(c_points[2].x, c_points[2].y, c_points[2].z),
			vec3(c_points[1].x, c_points[1].y, c_points[1].z),
			vec3(c_points[4].x, c_points[4].y, c_points[4].z),
			vec3(c_points[3].x, c_points[3].y, c_points[3].z));
		plnpoint = &pln2;
		DrawMesh(plnpoint);
	}
}

GLfloat PlaneEdgeToPlaneIntersection(Plane *pe, Plane *p, GLuint aboveID, GLuint BelowID) {
	pe->UpdateEdges();
	p->UpdateEdges();
	vec3 c_points[36];
	int l = 0;

	GLfloat *vert = p->getVertices();
	GLfloat x, y, z;

	x = *vert;
	vert++;
	y = *vert;
	vert++;
	z = *vert;
	vert++;
	vec3 p1(x, y, z);

	x = *vert;
	vert++;
	y = *vert;
	vert++;
	z = *vert;
	vert++;
	vec3 p0(x, y, z);

	x = *vert;
	vert++;
	y = *vert;
	vert++;
	z = *vert;
	vert++;
	vec3 p2(x, y, z);

	vec3 l0, l1;

	vec3 l01;

	vec3 p01, p02;

	float t, u, v, det;

	for (int i = 0; i < 4; i++) {
		l0 = pe->getLineStart(i);
		l1 = pe->getLineEnd(i);

		l01 = l1 - l0;
		p01 = p1 - p0;
		p02 = p2 - p0;

		GLfloat viiva[6] = { l0.x, l0.y, l0.z, l0.x + l01.x, l0.y + l01.y, l0.z + l01.z };
		//cout << l01.x << "," << l01.y << "," << l01.z << endl;
		DrawLine(viiva);

		mat3 m1 = mat3(l01, p01, p02);

		vec3 m2 = vec3(l0 - p0);

		if (determinant(m1)) {
			vec3 f = inverse(m1) * m2;

			t = f.x;
			u = f.y;
			v = f.z;
			if (t > -1 && t < 0) {
				vec3 finl = (l0 + (-t * l01));
				//cout << finl.x << "," << finl.y << "," << finl.z << endl;
				//GLfloat points[6] = { l0.x, l0.y, l0.z, finl.x, finl.y, finl.z };
				//DrawLine(points);
				GLfloat points[3] = { finl.x, finl.y, finl.z };
				//DrawPoint(points);
				c_points[l] = vec3(l0.x, l0.y, l0.z);
				l++;
				c_points[l] = vec3(finl.x, finl.y, finl.z);
				l++;
				c_points[l] = vec3(l1.x, l1.y, l1.z);
				l++;
				GLfloat line[6] = { l0.x, l0.y, l0.z, l1.x, l1.y, l1.z };
				//DrawLine(line);
			}
		}
		else {
			//cout << "Determinaatti nolla:" << determinant(m1) << endl;
		}
	}
	if (l > 0) {
		RenderRefraction(c_points, l, aboveID,  BelowID);
		return 0;
	}
	vec3 norm(0, 1, 0);

	GLfloat dotproduct = (norm.x * (l0.x - p0.x)) + (norm.y * (l0.y - p0.y)) + (norm.z * (l0.z - p0.z));
	
	return dotproduct;
}

void display(GLFWwindow* window)
{
	vector<Plane*> meshes;
	MeshFactory* MF = new MeshFactory();
	GLuint programID = LoadShaders("rotatevertex.glsl", "rotatefragment.glsl");
	GLuint programID2 = LoadShaders("rotatenvertex.glsl", "rotatenfragment.glsl");
	Plane * p;
	Plane *plane = MF->CreateMesh('p');
	Plane *cube = MF->CreateMesh('p');
	p = MF->CreateMesh('c');
	meshes.push_back(plane);
	meshes.push_back(cube);
	float m = 3.14159265358979 / 2;
	cube->Scale(cube->getVertices(), cube->v_size, 3.0f, 1.0f, 1.0f);
	cube->RotateX(m);
	cube->RotateZ(m/3);
	//cube->Translate(cube->getVertices(), cube->v_size, 0.0f, -1.0f, 0.0f);

	//cube->Translate(cube->getVertices(), cube->v_size, 0.0f, 1.0f, 0.0f);
	//cube->RotateZ(m);
	//cube->Scale(cube->getVertices(), cube->v_size, 1, 2, 1);
	//cube->Translate(cube->getVertices(), cube->v_size, 0.0f, 3.0f, 0.0f);

	float translaatio = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective(60, (double)windowWidth / (double)windowHeight, 0.1, 100);

		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0, -1, -7);

		//Shader Link
		glUseProgram(programID);

		//Shader update
		float dTime = glfwGetTime();
		int loc = glGetUniformLocation(programID, "time");
		glProgramUniform1f(programID, loc, 0);

		//cube->RotateX(0.001f);
		//cube->RotateY(0.001f);

		
		//cube->Translate(cube->getVertices(), cube->v_size, 0.0f, -translaatio, 0.0f);
		cube->RotateZ(0.001f);
		cube->RotateY(0.001f);
		cube->RotateX(0.001f);
		///translaatio -= 0.0005f;
		//cube->Translate(cube->getVertices(), cube->v_size, 0.0f, translaatio, 0.0f);

		//cube->Scale(cube->getVertices(), cube->v_size, 1.001f, 1.001f, 1.001f);
		//cube->Translate(cube->getVertices(), cube->v_size, 0, -0.0005f, 0);

		//DrawMesh(cube);

		//Shader Link
		glUseProgram(programID2);

		//Shader update
		dTime = glfwGetTime();
		loc = glGetUniformLocation(programID2, "time");
		//glProgramUniform1f(programID2, loc, 1.0f);

		//plane->RotateX(0.001f);
		//DrawMesh(plane);

		glUseProgram(programID);
		GLfloat dp = PlaneEdgeToPlaneIntersection(cube, plane, programID, programID2);
		if (dp > 0) {
			glUseProgram(programID);
			DrawMesh(cube);
		}
		else if (dp < 0) {
			glUseProgram(programID2);
			DrawMesh(cube);
		}
		//glUseProgram(programID);
		//DrawMesh(cube);
		

		// Update Screen
		glfwSwapBuffers(window);

		// Check for any input, or window movement
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{	
	GLFWwindow* window = initWindow(1024, 720);
	if (NULL != window)
	{
		display(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}