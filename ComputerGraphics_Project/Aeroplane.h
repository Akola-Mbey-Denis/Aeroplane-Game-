#pragma once
#include <glm/glm/glm.hpp> 
#include<glad/glad.h>
#include "texture.h"
#include "gameObject.h"
class Aeroplane : public GameObject
{
public:
	// Ball state	
	GLfloat   size;
	GLboolean Stuck;


	Aeroplane();
	Aeroplane(glm::vec2 pos, GLfloat size, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void      Reset(glm::vec2 position, glm::vec2 velocity);
};

