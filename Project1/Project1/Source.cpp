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

// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
Ball updatePhysics(Ball ball, double deltaTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);



// VARIABLES
bool		running = true;
int const number_of_balls = 10;
int const dimensions = 3;
Graphics	myGraphics;		// Runing all the graphics in this object

INPUT_RECORD InputRecord;
COORD coord;

Cube		myCube;
Sphere		mySphere, mySphere2;
Sphere mySpheres[number_of_balls];
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;
float bounds[6];
float t = 0.001f;					// Global variable for animation
float g = -9.81f;					// Gravitational force
double prevTime = glfwGetTime();	//Prev time
Ball ball, ball2;
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

	//Random balls everywhere
	/*for (int i = 0; i < number_of_balls; i++) {
		balls[i].radius = 1;
		balls[i].position = glm::vec3(-3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -6.0f);
		balls[i].velocity = glm::vec3(-3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))));
		balls[i].acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	}*/

	ball.radius = 1;
	ball.setMass(27);
	ball.position = glm::vec3(1.0f, 2.0f, -6.0f);
	ball.velocity = glm::vec3(3.0f, 1.0f, 1.0f);
	ball.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);


	
	//Exploding balls from one point
	for (int i = 0; i < number_of_balls; i++) {
		balls[i].radius = 1;
		balls[i].mass= 28;
		balls[i].alive =1;
		balls[i].position = ball.position;
		//balls[i].velocity = glm::vec3(1.0f, 1.0f, 1.0f);
		balls[i].angular_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		//balls[i].angular_velocity = glm::vec3( - 10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
		balls[i].velocity = glm::vec3(-10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))), -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20))));
		balls[i].acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
		
		printf("Kinetic Energy: %f", balls[i].KineticEnergy());
		printf(" Position: %f %f %f", balls[i].position.x, balls[i].position.y, balls[i].position.z);
		printf(" Velocity: %f %f %f", balls[i].velocity.x, balls[i].velocity.y, balls[i].velocity.z);
		printf(" Potential Energy: %f", balls[i].PotentialEnergy());
		printf(" Mass: %f", balls[i].mass);
		printf(" Alive: %d", balls[i].alive);
		printf(" Momentum: %f %f %f", balls[i].Momentum().x, balls[i].Momentum().y, balls[i].Momentum().z);
	}

	


	ball2.radius = 1;
	ball2.position = glm::vec3(-1.0f, -2.0f, -6.0f);
	ball2.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	ball2.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys
																			// MAIN LOOP run until the window is closed
	do {



		coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

	

		double currentTime = glfwGetTime();		// retrieve timelapse
		double deltaTime = currentTime - prevTime;
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.
		for (int i = 0; i < number_of_balls; i++) {
			balls[i] = updatePhysics(balls[i], deltaTime);
		}
		ball = updatePhysics(ball, deltaTime);
		ball2 = updatePhysics(ball2, deltaTime);
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

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();

	for (int i = 0; i < number_of_balls; i++) {
		mySpheres[i].Load();
		mySpheres[i].fillColor = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	}

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	mySphere2.Load();
	mySphere2.fillColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myGraphics.SetOptimisations();		// Cull and depth testing
}


void update(double currentTime) {

	// Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	//glm::mat4 mv_matrix_cube =
	//	glm::translate(glm::vec3(2.0f, 0.0f, -6.0f)) *
	//	glm::rotate(t, glm::vec3(0.0f, 1.0f, 0.0f)) *
	//	glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
	//	glm::mat4(1.0f);
	//myCube.mv_matrix = mv_matrix_cube;
	//myCube.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_spheres[number_of_balls];

	for (int i = 0; i < number_of_balls; i++) {
		mv_matrix_spheres[i] =
			glm::translate(balls[i].position) *
			glm::rotate(-t, balls[i].angular_velocity) *
			glm::mat4(1.0f);
		mySpheres[i].mv_matrix = mv_matrix_spheres[i];
		mySpheres[i].proj_matrix = myGraphics.proj_matrix;
	}

	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(ball.position) *
		glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere; 
	mySphere.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_sphere2 =
		glm::translate(ball2.position) *
		glm::mat4(1.0f);
	mySphere2.mv_matrix = mv_matrix_sphere2;
	mySphere2.proj_matrix = myGraphics.proj_matrix;

	//Calculate Arrows translations (note: arrow model points up)
	//glm::mat4 mv_matrix_x =
	//	glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
	//	glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
	//	glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
	//	glm::mat4(1.0f);
	//arrowX.mv_matrix = mv_matrix_x;
	//arrowX.proj_matrix = myGraphics.proj_matrix;

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

float update_vector(float derivative, float deltaTime) {
	return derivative*deltaTime;
}

Ball updatePhysics(Ball ball, double deltaTime)
{
	if (ball.position.y - ball.radius <= 0) {
		ball.velocity.x *= 0.999;
		ball.velocity.z *= 0.999;
	}

	if (ball.position.x + ball.velocity.x*deltaTime >= -3.0 + ball.radius && ball.position.x + ball.velocity.x*deltaTime <= 3.0 - ball.radius) {
		ball.position.x += ball.velocity.x*deltaTime;
	}
	if (ball.position.x + ball.velocity.x*deltaTime <= -3.0 + ball.radius || ball.position.x + ball.velocity.x*deltaTime >= 3.0 - ball.radius) {
		ball.velocity.x = -ball.velocity.x;
		if (ball.position.x <= -3.0 + ball.radius) {
			ball.velocity.x -= 0.2;
		}
		if (ball.position.x >= 3.0 - ball.radius) {
			ball.velocity.x += 0.2;
		}
	}

	if (ball.position.y + ball.velocity.y*deltaTime >= -3.0 + ball.radius && ball.position.y + ball.velocity.y*deltaTime <= 10.0 - ball.radius) {
		ball.position.y += ball.velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		ball.velocity.y += g*deltaTime;
	}
	if (ball.position.y + ball.velocity.y*deltaTime <= -3.0 + ball.radius || ball.position.y + ball.velocity.y*deltaTime >= 10.0 - ball.radius) {
		ball.velocity.y = -ball.velocity.y;
		ball.position.y += ball.velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		ball.velocity.y += g*deltaTime - 1;
		//Not sure if the following works
		ball.angular_velocity.x -= 0.1;
		ball.angular_velocity.y -= 0.1;
		ball.angular_velocity.z -= 0.1;
	}

	if (ball.position.z + ball.velocity.z*deltaTime >= -20.0 + ball.radius && ball.position.z + ball.velocity.z*deltaTime <= -5.0 - ball.radius) {
		ball.position.z += ball.velocity.z*deltaTime;
	}
	if (ball.position.z + ball.velocity.z*deltaTime <= -20.0 + ball.radius || ball.position.z + ball.velocity.z*deltaTime >= -5.0 - ball.radius) {
		ball.velocity.z = -ball.velocity.z;
		if (ball.position.z <= -20.0 + ball.radius) {
			ball.velocity.z -= 0.2;
		}
		if (ball.position.z >= -5.0 - ball.radius) {
			ball.velocity.z += 0.2;
		}
	}
		return ball;
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	
	// Draw
	//myCube.Draw();
	//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {


		for (int i = 0; i < number_of_balls; i++) {
			//if (balls[i].getAlive() == 1) {
				mySpheres[i].Draw();
			//}	
		}
	//}
	//mySphere.Draw();
	//mySphere2.Draw();
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

	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}