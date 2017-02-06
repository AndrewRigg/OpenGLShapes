//// 01_Pipeline_Interaction
//// Version up to lab 1.3.
//
//#include <iostream>
//using namespace std;
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <GLM/glm.hpp>
//#include <GLM/gtx/transform.hpp>
//
//void errorCallbackGLFW(int error, const char* description);
//void hintsGLFW();
//void endProgram();
//void render(double currentTime);
//void update(double currentTime);
//void setupRender();
//void startup();
//
//// VARIABLES
//GLFWwindow*		window;
//int				windowWidth = 640;
//int				windowHeight = 480;
//bool			running = true;
//
//GLuint          program;
//GLuint          vao;
//GLuint          buffer;
//GLint           mv_location;
//GLint           proj_location;
//float           aspect;
//glm::mat4		proj_matrix;
//
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
//	setupRender();								// setup some render variables.
//	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
//
//
//	do {										// MAIN LOOP run until the window is closed
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
//void setupRender() {
//	glfwSwapInterval(1);	// Ony render when synced (V SYNC)
//
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_SAMPLES, 0);
//	glfwWindowHint(GLFW_STEREO, GL_FALSE);
//}
//
//void startup() {
//	static const char * vs_source[] =
//	{
//		"#version 450 core                                                  \n"
//		"                                                                   \n"
//		"in vec4 position;                                                  \n"
//		"                                                                   \n"
//		"out VS_OUT                                                         \n"
//		"{                                                                  \n"
//		"    vec4 color;                                                    \n"
//		"} vs_out;                                                          \n"
//		"                                                                   \n"
//		"uniform mat4 mv_matrix;                                            \n"
//		"uniform mat4 proj_matrix;                                          \n"
//		"                                                                   \n"
//		"void main(void)                                                    \n"
//		"{                                                                  \n"
//		"    gl_Position = proj_matrix * mv_matrix * position;              \n"
//		"    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);      \n"
//		"}                                                                  \n"
//	};
//
//	static const char * fs_source[] =
//	{
//		"#version 450 core                                                  \n"
//		"                                                                   \n"
//		"out vec4 color;                                                    \n"
//		"                                                                   \n"
//		"in VS_OUT                                                          \n"
//		"{                                                                  \n"
//		"    vec4 color;                                                    \n"
//		"} fs_in;                                                           \n"
//		"                                                                   \n"
//		"void main(void)                                                    \n"
//		"{                                                                  \n"
//		"    color = fs_in.color;                                           \n"
//		"}                                                                  \n"
//	};
//
//	program = glCreateProgram();
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, fs_source, NULL);
//	glCompileShader(fs);
//
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, vs_source, NULL);
//	glCompileShader(vs);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//
//	glLinkProgram(program);
//
//
//
//	static const GLfloat vertex_positions[] =
//	{
//		-0.25f,  0.25f, -0.25f,
//		-0.25f, -0.25f, -0.25f,
//		0.25f, -0.25f, -0.25f,
//
//		0.25f, -0.25f, -0.25f,
//		0.25f,  0.25f, -0.25f,
//		-0.25f,  0.25f, -0.25f,
//
//		0.25f, -0.25f, -0.25f,
//		0.25f, -0.25f,  0.25f,
//		0.25f,  0.25f, -0.25f,
//
//		0.25f, -0.25f,  0.25f,
//		0.25f,  0.25f,  0.25f,
//		0.25f,  0.25f, -0.25f,
//
//		0.25f, -0.25f,  0.25f,
//		-0.25f, -0.25f,  0.25f,
//		0.25f,  0.25f,  0.25f,
//
//		-0.25f, -0.25f,  0.25f,
//		-0.25f,  0.25f,  0.25f,
//		0.25f,  0.25f,  0.25f,
//
//		-0.25f, -0.25f,  0.25f,
//		-0.25f, -0.25f, -0.25f,
//		-0.25f,  0.25f,  0.25f,
//
//		-0.25f, -0.25f, -0.25f,
//		-0.25f,  0.25f, -0.25f,
//		-0.25f,  0.25f,  0.25f,
//
//		-0.25f, -0.25f,  0.25f,
//		0.25f, -0.25f,  0.25f,
//		0.25f, -0.25f, -0.25f,
//
//		0.25f, -0.25f, -0.25f,
//		-0.25f, -0.25f, -0.25f,
//		-0.25f, -0.25f,  0.25f,
//
//		-0.25f,  0.25f, -0.25f,
//		0.25f,  0.25f, -0.25f,
//		0.25f,  0.25f,  0.25f,
//
//		0.25f,  0.25f,  0.25f,
//		-0.25f,  0.25f,  0.25f,
//		-0.25f,  0.25f, -0.25f
//	};
//
//	mv_location = glGetUniformLocation(program, "mv_matrix");
//	proj_location = glGetUniformLocation(program, "proj_matrix");
//
//	// Calculate proj_matrix for the first time.
//	aspect = (float)windowWidth / (float)windowHeight;
//	proj_matrix = glm::perspective(50.0f, aspect, 0.1f, 1000.0f);
//
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//	glBufferData(GL_ARRAY_BUFFER,
//		sizeof(vertex_positions),
//		vertex_positions,
//		GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	glEnableVertexAttribArray(0);
//
//	glEnable(GL_CULL_FACE);
//	glFrontFace(GL_CW);
//
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);
//}
//
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
//
//	static const GLfloat one = 1.0f;
//	glClearBufferfv(GL_DEPTH, 0, &one);
//
//	glUseProgram(program);
//
//	glUniformMatrix4fv(proj_location, 1, GL_FALSE, &proj_matrix[0][0]);
//	glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
//	mv_matrix = glm::rotate(mv_matrix, 10.0f, glm::vec3(-1.0f, -1.0f, 0.0f));
//	glUniformMatrix4fv(mv_location, 1, GL_FALSE, &mv_matrix[0][0]);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//}