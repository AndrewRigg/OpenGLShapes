// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// 
// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"
#include "Physics.h"
#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <vector>

// FUNCTIONS
void render(float currentTime);
void update(float currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void explode();
float randNum(float p1, float p1a);
glm::vec3 randNum3(float p1, float p1a, float p2, float p2a, float p3, float p3a);
glm::vec4 randNum4(float p1, float p1a, float p2, float p2a, float p3, float p3a, float p4, float p4a);

// VARIABLES
bool		running = true;
int const number_of_balls = 200;
int const dimensions = 3;
Graphics	myGraphics;		// Runing all the graphics in this object

INPUT_RECORD InputRecord;
COORD coord;

Wall		myWall;
Plane		myPlane;
Cube		myCube;
Sphere		mySphere;
Sphere mySpheres[number_of_balls];
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;
float scale = 0.01;
float scales[number_of_balls];
float transparency[number_of_balls];
float rate = 0.001;
float ballTransparency;
float bounds[6];
float t = 0.001f;					// Global variable for animation
float factor = 10;					//multiplier for gravity (distance of pixels is not m)
float g = -9.81;					// Gravitational force
float prevTime = glfwGetTime();	//Prev time
Ball ball;
vector<Ball> ball_vec;
Ball balls[number_of_balls];

int main()
{
	srand(static_cast <unsigned> (time(0)));
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	bounds[0] = -3;
	bounds[1] = 3;
	bounds[2] = -3;
	bounds[3] = 3;
	bounds[4] = -3;
	bounds[5] = 3;

	ballTransparency = 1.0;
	ball.lifeTime = 100000;
	ball.radius = 1;
	ball.setMass(27);
	ball.rate = 10;
	ball.position = glm::vec3(1.0f, 2.0f, -6.0f);
	ball.velocity = glm::vec3(3.0f, 1.0f, 1.0f);
	ball.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys
																			// MAIN LOOP run until the window is closed
	do {
		coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

		float mousePosX = coord.X;
		float mousePosY = coord.Y;
		
		float currentTime = glfwGetTime();		// retrieve timelapse
		float deltaTime = currentTime - prevTime;
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.
		for (int i = 0; i < number_of_balls; i++) {
			//balls[i] = updatePhysics(balls[i], deltaTime);
			balls[i].updatePhysics(deltaTime);
		}
		//ball = updatePhysics(ball, deltaTime);
		ball.updatePhysics(deltaTime);
		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)
		prevTime = currentTime;

		//running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		//running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void explode() {
	//Exploding balls from one point
	for (int i = 0; i < number_of_balls; i++) {
		transparency[i] = 1.0;
		balls[i].radius = 1;
		balls[i].mass = 0;
		balls[i].lifeTime = randNum(100,200);
		balls[i].position = ball.position;
		//balls[i].velocity = glm::vec3(1.0f, 1.0f, 1.0f);
		//balls[i].angular_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		balls[i].angular_velocity = randNum3(-1,2,-1,2,-1,2);
		balls[i].velocity = randNum3(-20, 40, -20, 40, -20, 40);
		balls[i].acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
		//generate random size between p1 and p1a weighted more towards p1
		//scales[i] = randNum(0.01, 0.5);
		//scales[i] = randNum(0.01, randNum(0.01, 0.5));
		scales[i] = randNum(0.01,randNum(0.01, randNum(0.01, 0.5)));
		ball_vec.push_back(balls[i]);
	}
}

float randNum(float param1, float param1a) {
	return (param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))));
}

glm::vec4 randNum4(float param1, float param1a, float param2, float param2a, float param3, float param3a, float param4, float param4a){
	return glm::vec4(param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))), 
		param2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param2a))), param3 + 
		static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param3a))), param4 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param4a))));
}

glm::vec3 randNum3(float param1, float param1a, float param2, float param2a, float param3, float param3a) {
	return glm::vec3(param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))), 
		param2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param2a))), 
		param3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param3a))));
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();

	for (int i = 0; i < number_of_balls; i++) {
		mySpheres[i].Load();
		//mySpheres[i].fillColor = randNum4(0,1,0,1,0,1,0,1);
	}

	myWall.Load();
	myWall.fillColor = glm::vec4(0.7f, 0.7f, 0.7f, 0.5f);

	myPlane.Load();
	myPlane.fillColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myGraphics.SetOptimisations();		// Cull and depth testing
}


void update(float currentTime) {

	// Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(1.0f, 0.0f, -6.0f)) *
		//glm::rotate(t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		//glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1.0f, 1.0f, 2.0f)) *
		glm::mat4(1.0f);
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;

	vector <glm::mat4> mv_matrix_spheres[number_of_balls];

	for (int i = 0; i < number_of_balls; i++) {
		glm::mat4 mv_matrix_spheres =
			glm::translate(balls[i].position) *
			//glm::rotate(-t, balls[i].angular_velocity) *
			glm::scale(glm::vec3(scales[i], scales[i], scales[i])) *		//trial
			glm::mat4(1.0f);
		mySpheres[i].mv_matrix = mv_matrix_spheres;
		mySpheres[i].proj_matrix = myGraphics.proj_matrix;
		mySpheres[i].fillColor = glm::vec4(0.8,0.2,0.2,transparency[i]);
		mySpheres[i].lineColor = glm::vec4(0.4, 0.0, 0.0, transparency[i]);
	}

	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(ball.position) *
		//glm::rotate(-ball.rate, glm::vec3(ball.angular_velocity)) *
		//glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
		//glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere; 
	mySphere.proj_matrix = myGraphics.proj_matrix;
	mySphere.fillColor = glm::vec4(0.0, 1.0, 0.0, ballTransparency);
	mySphere.lineColor = glm::vec4(0.0, 0.0, 0.0, ballTransparency);

	glm::mat4 mv_matrix_plane =
		glm::translate(glm::vec3( 10, -3, -100)) *
		//glm::rotate(-ball.rate, glm::vec3(ball.angular_velocity)) *
		//glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
		//glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) *
		glm::mat4(1.0f);
	myPlane .mv_matrix = mv_matrix_plane;
	myPlane.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_wall =
		glm::translate(glm::vec3(8, -3, -100)) *
		//glm::rotate(-ball.rate, glm::vec3(ball.angular_velocity)) *
		//glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
		//glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) *
		glm::mat4(1.0f);
	myWall.mv_matrix = mv_matrix_wall;
	myWall.proj_matrix = myGraphics.proj_matrix;

	t += 0.01f; // increment movement variable
}

void render(float currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	
	float check = 1.0;
		for (int i = 0; i < number_of_balls; i++) {
			if (!balls[i].alive()) {
				//printf("Lifetime: %f", balls[i].lifeTime);
				transparency[i] -= 0.03;
				check = transparency[i];
			}
			if (check > 0) {
				mySpheres[i].Draw();
			}
	}
	//}
		if (ball.alive()) {
			ballTransparency = (1+ballTransparency) * ballTransparency + 0.0001;
			if (ballTransparency >= 0.01) {
				mySphere.Draw();
			}
		}
		myPlane.Draw();
		//myWall.Draw();
	/*arrowX.Draw();
	arrowY.Draw();
	arrowZ.Draw();*/
}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);


	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		//ball.lifeTime = 0;
		ballTransparency = 0.0;
		explode();
		ball.position = randNum3(-5, 10, -3, 8, -20, 15);
	}
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}
