#pragma once
#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

void ErrorCallbackGLFW(int error, const char* description);

class Graphics {
public:
	Graphics();
	~Graphics();

	int Init();
	void hintsGLFW();
	void SetupRender();
	void endProgram();
	void SetOptimisations();
	void ClearViewport();


	GLFWwindow*		window;
	//changing these makes no difference seemingly
	//int				windowWidth = 640;
	int				windowWidth = 1000;
	//int				windowHeight = 480;
	int				windowHeight = 600;
	float           aspect;
	glm::mat4		proj_matrix = glm::mat4(1.0f);

};