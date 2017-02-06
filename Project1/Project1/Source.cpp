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


// VARIABLES
bool		running = true;
int const number_of_balls = 2;
int const dimensions = 3;
Graphics	myGraphics;		// Runing all the graphics in this object

INPUT_RECORD InputRecord;
COORD coord;

Cube		myCube;
Sphere		mySphere;
Sphere mySpheres[number_of_balls];
std::vector<Sphere> spheres;
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;
float scale = 0.5;
float rate = 0.001;
float t = 0.001f;					// Global variable for animation
float factor = 10;					//multiplier for gravity (distance of pixels is not m)
float g = -9.81;					// Gravitational force
float prevTime = glfwGetTime();	//Prev time
Ball initial_ball;
std::vector<Ball> ball_vec;
Ball balls[number_of_balls];

int main()
{
	
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	initial_ball.radius = 1;
	initial_ball.setMass(27);
	initial_ball.rate = 10;
	initial_ball.position = glm::vec3(1.0f, 2.0f, -6.0f);
	initial_ball.velocity = glm::vec3(3.0f, 1.0f, 1.0f);
	initial_ball.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	startup();
	
	// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys
																			// MAIN LOOP run until the window is closed
	do {
		coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
		
		float currentTime = glfwGetTime();		// retrieve timelapse
		float deltaTime = currentTime - prevTime;
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.
		//for (int i = 0; i < number_of_balls; i++) {
		//	//balls[i] = updatePhysics(balls[i], deltaTime);
		//	balls[i].updatePhysics(deltaTime);
		//}

		for (Ball b : ball_vec) {
			b.updatePhysics(deltaTime);
		}
		//ball = updatePhysics(ball, deltaTime);
		initial_ball.updatePhysics(deltaTime);
		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)
		prevTime = currentTime;

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void explode() {
	//Exploding balls from one point
	srand(static_cast <unsigned> (time(0)));

	for (int i = 0; i < number_of_balls; i++) {
		Sphere sphere;
		Ball ball;
		sphere.Load();
		sphere.fillColor = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		spheres.push_back(sphere);
		ball.radius = 1;
		ball.mass = 28;
		ball.lifeTime = 100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1000)));
		ball.position = ball.position;
		//ball.velocity = glm::vec3(1.0f, 1.0f, 1.0f);
		//ball.angular_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		ball.angular_velocity = glm::vec3( - 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))), -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))), -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2))));
		ball.velocity = glm::vec3(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
		ball.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
		ball_vec.push_back(ball);
	}
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();


	/*for (int i = 0; i < number_of_balls; i++) {
		mySpheres[i].Load();
		mySpheres[i].fillColor = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	}*/


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



	//for (int i = 0; i < number_of_balls; i++) {
	//	glm::mat4 mv_matrix_sphere =
	//		glm::translate(balls[i].position) *
	//		glm::rotate(-t, balls[i].angular_velocity) *
	//		glm::scale(glm::vec3(scale, scale, scale)) *		//trial
	//		glm::mat4(1.0f);
	//	mySpheres[i].mv_matrix = mv_matrix_sphere;
	//	mySpheres[i].proj_matrix = myGraphics.proj_matrix;
	//}



	//***************CHECK
	int i = 0;
	for (Ball b: ball_vec) {
		glm::mat4 mv_matrix_sphere =
			glm::translate(b.position) *
			glm::rotate(-t, b.angular_velocity) *
			glm::scale(glm::vec3(scale, scale, scale)) *		//trial
			glm::mat4(1.0f);
		spheres.at(i).mv_matrix = mv_matrix_sphere;
		spheres.at(i).proj_matrix = myGraphics.proj_matrix;
		i++;
	}

	//************
	

	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(initial_ball.position) *
		glm::rotate(-initial_ball.rate, glm::vec3(initial_ball.angular_velocity)) *
		glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere; 
	mySphere.proj_matrix = myGraphics.proj_matrix;


	//glm::mat4 mv_matrix_y =
	//	glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
	//	//glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *	// already model pointing up
	//	glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
	//	glm::mat4(1.0f);
	//arrowY.mv_matrix = mv_matrix_y;
	//arrowY.proj_matrix = myGraphics.proj_matrix;

	//glm::mat4 mv_matrix_z =
	//	glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
	//	glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
	//	glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
	//	glm::mat4(1.0f);
	//arrowZ.mv_matrix = mv_matrix_z;
	//arrowZ.proj_matrix = myGraphics.proj_matrix;

	t += 0.01f; // increment movement variable
}

void render(float currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	
	// Draw
	//myCube.Draw();
	//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
	
	
		for (Sphere s: spheres) {
			//if (ball_vec.at(i).alive()) {
				//printf("Lifetime: %f", balls[i].lifeTime);
				s.Draw();
			//}
	}
	//}
	mySphere.Draw();
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
		explode();
	}
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}
