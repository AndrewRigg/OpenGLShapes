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
#include "Boids.h"
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
int const number_of_boids = 100;
int const dimensions = 3;
Graphics	myGraphics;		// Runing all the graphics in this object

INPUT_RECORD InputRecord;
COORD coord;

Cube		myCube;
Sphere		mySphere;
Sphere mySpheres[number_of_boids];
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;
float scale = 0.3;
float rate = 0.001;
float t = 0.001f;					// Global variable for animation
float factor = 10;					//multiplier for gravity (distance of pixels is not m)
float g = -9.81;					// Gravitational force
float prevTime = glfwGetTime();	//Prev time
Boid boid;
vector<Boid> boid_vec;
Boid boids[number_of_boids];

int main()
{

	srand(static_cast <unsigned> (time(0)));
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	//Random Boids everywhere
	for (int i = 0; i < number_of_boids; i++) {
		boids[i].radius = 1;
		boids[i].position = glm::vec3(-3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -6.0f);
		boids[i].velocity = glm::vec3(-3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))), -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6))));
		boids[i].acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	boid.radius = 1;
	boid.setMass(27);
	boid.rate = 10;
	boid.position = glm::vec3(1.0f, 2.0f, -6.0f);
	boid.velocity = glm::vec3(3.0f, 1.0f, 1.0f);
	boid.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	//Boid_vec.push_back(Boid);

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
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
		for (int i = 0; i < number_of_boids; i++) {
			//boids[i] = updatePhysics(Boids[i], deltaTime);
			boids[i].updatePhysics(deltaTime);
		}
		//boid = updatePhysics(Boid, deltaTime);
		boid.updatePhysics(deltaTime);
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

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();

	for (int i = 0; i < number_of_boids; i++) {
		mySpheres[i].Load();
		mySpheres[i].fillColor = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	}

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

	vector <glm::mat4> mv_matrix_spheres[number_of_boids];

	for (int i = 0; i < number_of_boids; i++) {
		glm::mat4 mv_matrix_spheres =
			glm::translate(boids[i].position) *
			//glm::rotate(-t, Boids[i].angular_velocity) *
			glm::scale(glm::vec3(scale, scale, scale)) *		//trial
			glm::mat4(1.0f);
		mySpheres[i].mv_matrix = mv_matrix_spheres;
		mySpheres[i].proj_matrix = myGraphics.proj_matrix;
	}

	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(boid.position) *
		glm::rotate(-boid.rate, glm::vec3(boid.angular_velocity)) *
		//glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
		//glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere; 
	mySphere.proj_matrix = myGraphics.proj_matrix;

	t += 0.01f; // increment movement variable
}

void render(float currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	
	// Draw
	//myCube.Draw();
	//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
	
	
		for (int i = 0; i < number_of_boids; i++) {
			//if (Boids[i].alive()) {
				//printf("Lifetime: %f", Boids[i].lifeTime);
				mySpheres[i].Draw();
		//	}
	}
	//}
	//mySphere.Draw();
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