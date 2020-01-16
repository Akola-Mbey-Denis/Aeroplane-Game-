#include "game.h"
#include "resourceManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
//#include<irrKlang/irrKlang.h> 
//using namespace irrklang;



const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;


 
Game Aeroplane(SCREEN_WIDTH, SCREEN_HEIGHT);

void gameConsole ()//Display game console messages
{
	std::cout << "Welcome to Aeroplane Game!" << std::endl;
	std::cout << "To play this Game:" << std::endl;
	std::cout << "Press the BackSpace Key to fly the aeroplane." << std::endl;
	std::cout<<"Press down key A to change flying direction" << std::endl;
	std::cout << "Press down Key D to change the game console background and the aeroplane object." << std::endl;
	std::cout << "Press the key F to end the game!" << std::endl;
}

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Aeroplane.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Aeroplane.Keys[key] = GL_FALSE;
	}
}

void resizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool initialiseEnvironment(GLFWwindow** window) {
	// Initialise, configure, instantiate GLFW window
	if (!glfwInit()) {
		std::cout << "Failed to initialise GLFW" << std::endl;
		return false;
	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	*window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aeroplane Game ", nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create window";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, resizeCallback);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return false;

	}

	// Set drawing area
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	return true;
}
//Driver code
int main(void)
{
	GLFWwindow* window;
	if (!initialiseEnvironment(&window))
	{
		return -1;
	}


	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game 
	Aeroplane.Init();
	 

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	 

	Aeroplane.State = GAME_ACTIVE;
	 
	gameConsole ();


	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		
		//deltaTime = 0.001f;
		// Manage user input
		Aeroplane.ProcessInput(deltaTime);

		// Update Game state
		Aeroplane.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Aeroplane.Render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

