//// 01_Pipeline_Interaction
//// Version up to lab 1.2.
//
//#include <iostream>
//using namespace std;
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//void errorCallbackGLFW(int error, const char* description);
//void hintsGLFW();
//void endProgram();
//void render(double currentTime);
//void update(double currentTime);
//
//// VARIABLES
//GLFWwindow*		window;
//int				windowWidth = 640;
//int				windowHeight = 480;
//bool			running = true;
//
//
//int main()
//{
//	if (!glfwInit()) {							// Checking for GLFW
//		cout << "Could not initialise GLFW...";
//		return 0;
//	}
//
//	glfwSetErrorCallback(errorCallbackGLFW);	// Setup a function to catch and display all GLFW errors.
//
//	hintsGLFW();								// Setup glfw with various hints.		
//
//												// Start a window using GLFW
//	string title = "My OpenGL Application";
//	window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
//	if (!window) {								// Window or OpenGL context creation failed
//		cout << "Could not initialise GLFW...";
//		endProgram();
//		return 0;
//	}
//
//	glfwMakeContextCurrent(window);				// making the OpenGL context current
//
//												// Start GLEW (note: always initialise GLEW after creating your window context.)
//	glewExperimental = GL_TRUE;					// hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
//	GLenum errGLEW = glewInit();
//	if (GLEW_OK != errGLEW) {					// Problems starting GLEW?
//		cout << "Could not initialise GLEW...";
//		endProgram();
//		return 0;
//	}
//
//	do {										// run until the window is closed
//
//		double currentTime = glfwGetTime();		// retrieve timelapse
//		glfwPollEvents();						// poll callbacks
//		update(currentTime);					// update (physics, animation, structures, etc)
//		render(currentTime);					// call render function.
//
//		glfwSwapBuffers(window);				// swap buffers (avoid flickering and tearing)
//		
//
//		running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
//		running &= (glfwWindowShouldClose(window) != GL_TRUE);
//	} while (running);
//
//	endProgram();			// Close and clean everything up...
//
//
//	cout << "\nPress any key to continue...\n";
//	cin.ignore(); cin.get(); // delay closing console to read debugging errors.
//	
//	return 0; 
//}
//
//void errorCallbackGLFW(int error, const char* description) {
//	cout << "Error GLFW: " << description << "\n";
//}
//
//void hintsGLFW() {
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);			// Create context in debug mode - for debug message callback
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
//}
//
//void endProgram() {
//	glfwMakeContextCurrent(window);		// destroys window handler
//	glfwTerminate();	// destroys all windows and releases resources.
//}
//
//void update(double currentTime) {
//
//}
//
//void render(double currentTime) {
//	static const GLfloat silver[] = { 0.9f, 0.9f, 0.9f, 1.0f };
//
//	glViewport(0, 0, windowWidth, windowHeight);
//	glClearBufferfv(GL_COLOR, 0, silver);
//}
