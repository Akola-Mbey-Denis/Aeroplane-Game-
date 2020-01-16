#pragma once
#include<glad/glad.h>
#include "GameLevels.h"
#include "gameObject.h"
#include <glm/glm/glm.hpp>
#include "PowerUp.h"
// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};


// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);
// Initial velocity of the Aeroplane
const glm::vec2 INITIAL_AEROPLANE_VELOCITY (100.0f, -350.0f);
// Radius of the ball object
const GLfloat AEROPLANE_SIZE = 13.0f;

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;
	std::vector<GameLevels> Levels;
	GLuint                 Level;
	std::vector<PowerUp>  PowerUps;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	//powerup settings
	void SpawnPowerUps (GameObject& block);
	void ActivatePowerUp (PowerUp& obj );
	void UpdatePowerUps (GLfloat dt);
	//collision 
	void  DoCollisions ();
	 
	 
	// Reset
	void ResetLevel ();
	void ResetPlayer ();
};