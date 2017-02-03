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

// FUNCTIONS
void render(double currentTime);
void update(double currentTime, glm::vec3 position);
Ball updatePhysics(Ball ball, double deltaTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Cube		myCube;
Sphere		mySphere;
Arrow		arrowX;
Arrow		arrowY;
Arrow		arrowZ;



float t = 0.001f;					// Global variable for animation
float g = -9.81f;					// Gravitational force

int main()
{
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	
	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
												// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys
			
	double currentTime = glfwGetTime();	
	Ball ball;
	ball.radius = 1;
	ball.position = glm::vec3(0.0f, 2.0f, -6.0f);
	ball.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	ball.acceleration = glm::vec3(0.0f, -9.8f, 0.0f);	

														// MAIN LOOP run until the window is closed
	do {
			// retrieve timelapse
		double prevTime = currentTime;
		currentTime = glfwGetTime();
		double deltaTime = currentTime - prevTime;
		glfwPollEvents();						// poll callbacks
		ball = updatePhysics(ball, deltaTime);
		update(currentTime, ball.position);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.
		
		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)
		
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

	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	arrowX.Load(); arrowY.Load(); arrowZ.Load();
	arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myGraphics.SetOptimisations();		// Cull and depth testing
}


void update(double currentTime, glm::vec3 position) {

	 //Calculate Cube movement ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	glm::mat4 mv_matrix_cube =
		glm::translate(glm::vec3(2.0f, 0.0f, -6.0f)) *
		glm::rotate(t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(t, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::mat4(1.0f);
	myCube.mv_matrix = mv_matrix_cube;
	myCube.proj_matrix = myGraphics.proj_matrix;




	// calculate Sphere movement
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(position)) *
		/*glm::rotate(-t, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(-t, glm::vec3(1.0f, 0.0f, 0.0f)) **/
		glm::mat4(1.0f);
	mySphere.mv_matrix = mv_matrix_sphere; 
	mySphere.proj_matrix = myGraphics.proj_matrix;

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

Ball updatePhysics(Ball ball, double deltaTime)
{

	//add friction if no longer bouncing
	if (ball.velocity.y == 0) {
		ball.velocity.x -= 0.05;
	}
	if (ball.position.x + ball.velocity.x*deltaTime >= -3.0 + ball.radius - 1 || ball.position.x + ball.velocity.x*deltaTime <= 3.0 - ball.radius + 1) {
		ball.position.x += ball.velocity.x*deltaTime;
		
	}

	if ((ball.position.x <= -3.0 + ball.radius) || (ball.position.x >= 3.0 - ball.radius)) {
		ball.velocity.x = -ball.velocity.x;
		if (ball.position.x <= -3.0 + ball.radius) {
			ball.velocity.x-=0.2;
		}
		if (ball.position.x >= 3.0 - ball.radius) {
			ball.velocity.x+= 0.2;
		}
	}
	
	if (ball.position.y + ball.velocity.y*deltaTime > -3.0 + ball.radius-1) {
		ball.position.y += ball.velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		ball.velocity.y += g*deltaTime;
	}
	
	
		if (ball.position.y <= -3.0 + ball.radius) {
		//The following line makes the ball stop at the ground.
		//h = -3.0 + ballRadius;
		//Reverses the direction of the velocity of the ball due an elastic collision.
			ball.velocity.y = -ball.velocity.y;
			ball.position.y += ball.velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
			ball.velocity.y += g*deltaTime -1.0;
		//Energy lost due to friction Fr reduces the speed after impact:
		//E(before) = E(after) = 0.5 * m * (u^2) = 0.5 * m * (v^2) + Ff
		//ie  sqrt((E - Ff)/(0.5*m)) = v
		//u = sqrt((0.5*m*pow(u, 2.0) - Ff) / (0.5*m));

	}
		return ball;
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	//myCube.Draw();
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

	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}