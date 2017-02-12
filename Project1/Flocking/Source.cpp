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
#include "Vectors.h"

// FUNCTIONS
void render(float currentTime);
void update(float currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
float randNum(float p1, float p1a);
vector3 randNum3(float p1, float p1a, float p2, float p2a, float p3, float p3a);
glm::vec4 randNum4(float p1, float p1a, float p2, float p2a, float p3, float p3a, float p4, float p4a);

// VARIABLES
bool		running = true;
int const number_of_boids = 50;
int const dimensions = 3;
Graphics	myGraphics;		// Runing all the graphics in this object

INPUT_RECORD InputRecord;
COORD coord;

Cube		myCube;
Sphere		mySphere;
Arrow mySpheres[number_of_boids];
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;
//vector3 previous [10];
vector3 previous;
float wander = 0;
float alignmentFactor = 1.0;
float cohesionFactor = 1.25;
float separationFactor = 0.9;
float scale = 0.5;
float rate = 0.001;
float t = 0.001f;					// Global variable for animation
float factor = 10;					//multiplier for gravity (distance of pixels is not m)
float g = 0;					// Gravitational force
float prevTime = glfwGetTime();	//Prev time
Boid boid;
vector<Boid> boid_vec;
Boid boids[number_of_boids];

int main()
{
	/*for (int i = 0; i < 10; i++) {
		previous[i] = vector3(0.0, 0.0, 0.0);
	}*/
	previous = vector3(0.0, 0.0, 0.0);
	srand(static_cast <unsigned> (time(0)));
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	//Random Boids everywhere
	for (int i = 0; i < number_of_boids; i++) {
		float spd = randNum(3, 4);
		boids[i].radius = 1;
		boids[i].position = randNum3(-3, 6, -3, 6, -20, 18);
		boids[i].velocity = randNum3(-spd, 2*spd, -spd, 2*spd, -spd, 2*spd);
		//boids[i].angular_velocity = boids[i].direction(previous);
		boids[i].angular_velocity = boids[i].direction();
		//boids[i].angular_velocity = randNum3(-3, 6, -3, 6, -3, 6);
	}

	boid.radius = 1;
	boid.setMass(27);
	boid.rate = 10;
	boid.position = vector3(1.0f, 2.0f, -6.0f);
	boid.velocity = vector3(3.0f, 1.0f, 1.0f);
	boid.acceleration = vector3(0.0f, 0.0f, 0.0f);
	//Boid_vec.push_back(Boid);

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

			vector3 alignment = boids[i].alignment(boids);
			vector3 cohesion = boids[i].cohesion(boids);
			vector3 separation = boids[i].separation(boids);

			float originalSpeed = boids[i].speed();
			
			boids[i].velocity.x += alignmentFactor*alignment.x + cohesionFactor*cohesion.x + separationFactor*separation.x+randNum(-wander, 2*wander);
			boids[i].velocity.y += alignmentFactor*alignment.y + cohesionFactor*cohesion.y + separationFactor*separation.y+randNum(-wander, 2*wander);
			boids[i].velocity.z += alignmentFactor*alignment.z + cohesionFactor*cohesion.z + separationFactor*separation.z+randNum(-wander, 2*wander);
			
	

			boids[i].velocity = glm::normalize(boids[i].velocity).operator*=(originalSpeed);
			boids[i].updatePhysics(deltaTime);
			
		}
		//boid = updatePhysics(Boid, deltaTime);
		boid.updatePhysics(deltaTime);
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


float randNum(float param1, float param1a) {
	return (param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))));
}

glm::vec4 randNum4(float param1, float param1a, float param2, float param2a, float param3, float param3a, float param4, float param4a) {
	return glm::vec4(param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))),
		param2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param2a))), param3 +
		static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param3a))), param4 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param4a))));
}

vector3 randNum3(float param1, float param1a, float param2, float param2a, float param3, float param3a) {
	return vector3(param1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param1a))),
		param2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param2a))),
		param3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (param3a))));
}

void startup() {

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	myCube.Load();
	myCube.fillColor = glm::vec4(0.5f, 0.5f, 0.0f, 0.5f);

	for (int i = 0; i < number_of_boids; i++) {
		mySpheres[i].Load();
		//mySpheres[i].fillColor = glm::vec4(0.55, 0.5, 0.6, 0.5);
		//mySpheres[i].lineColor = glm::vec4(0.45, 0.4, 0.5, 0.5);
		//mySpheres[i].fillColor = randNum4(0.2, 0.3, 0.15, 0.2, 0, 0.05, 1, 1);
		mySpheres[i].fillColor = randNum4(0, 1, 0, 1, 0, 1, 1, 1);
	}

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);	// You can change the shape fill colour, line colour or linewidth 

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myGraphics.SetOptimisations();		// Cull and depth testing
}


void update(float currentTime) {

	// Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(0.0f, -6.0f, -12.0f)) *
		//glm::rotate(t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		//glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(6.0f, 6.0f, 6.0f)) *
		glm::mat4(1.0f);
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;

	vector <glm::mat4> mv_matrix_spheres[number_of_boids];

	for (int i = 0; i < number_of_boids; i++) {
		glm::mat4 mv_matrix_spheres =
			glm::translate(glm::vec3 (boids[i].position.toVec3())) *
			//glm::rotate(1.0f, boids[i].direction(previous)) *
			glm::rotate(1.0f, glm::vec3 (boids[i].direction().toVec3())) *
			//glm::scale(glm::vec3(0.5*scale, 0.1*scale, scale)) *		//trial
			glm::scale(glm::vec3(scale, scale, scale)) *
			glm::mat4(1.0f);
		mySpheres[i].mv_matrix = mv_matrix_spheres;
		mySpheres[i].proj_matrix = myGraphics.proj_matrix;
		//previous[i%10] = boids[i].direction(previous);
		previous = boids[i].direction();
	}

	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3 (boid.position.toVec3())) *
		glm::rotate(-boid.rate, glm::vec3(boid.angular_velocity.toVec3())) *
		glm::rotate(-t, glm::vec3(0.1f, 1.0f, 0.0f)) *
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
		
	}
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}
