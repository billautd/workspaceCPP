#pragma once
#include "glad/glad.h"
#include "glm.hpp"

const GLuint SCREEN_HEIGHT{ 800 };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(ASPECT_RATIO * SCREEN_HEIGHT) };

//Player
const glm::vec2 INITIAL_PLAYER_SIZE{ 100.0f, 20.0f };
const GLfloat PLAYER_VELOCITY{ 500.0f };
const glm::vec2 INITIAL_PLAYER_POSITION{ SCREEN_WIDTH / 2.0f - INITIAL_PLAYER_SIZE.x / 2.0f, SCREEN_HEIGHT - INITIAL_PLAYER_SIZE.y };
const GLfloat MAX_PLAYER_SIZE{ 400.0f };

//Ball
const GLfloat BALL_RADIUS{ 12.5f };
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const glm::vec2 INITIAL_BALL_POSITION{ SCREEN_WIDTH / 2.0f - BALL_RADIUS, SCREEN_HEIGHT - INITIAL_PLAYER_SIZE.y - 2.0f * BALL_RADIUS };


//Directions
const glm::vec2 compass[]{
	glm::vec2(0.0f, 1.0f),	// up
	glm::vec2(1.0f, 0.0f),	// right
	glm::vec2(0.0f, -1.0f),	// down
	glm::vec2(-1.0f, 0.0f)	// left
};

//Powerups
const glm::vec2 POWERUP_SIZE{60.0F, 20.0f};
const glm::vec2 POWERUP_VELOCITY{0.0F, 150.0f};


//Particles
const GLuint MAX_PARTICLES{ 500 };
const GLfloat PARTICLE_SCALE{ 10.0f };

//Post processing shader
const GLfloat PIXEL_OFFSET = 1.0f / 300.0f;
const GLfloat OFFSETS[9][2]{
    { -PIXEL_OFFSET,  PIXEL_OFFSET  },  // top-left
    {  0.0f,    PIXEL_OFFSET  },  // top-center
    {  PIXEL_OFFSET,  PIXEL_OFFSET  },  // top-right
    { -PIXEL_OFFSET,  0.0f    },  // center-left
    {  0.0f,    0.0f    },  // center-center
    {  PIXEL_OFFSET,  0.0f    },  // center - right
    { -PIXEL_OFFSET, -PIXEL_OFFSET  },  // bottom-left
    {  0.0f,   -PIXEL_OFFSET  },  // bottom-center
    {  PIXEL_OFFSET, -PIXEL_OFFSET  }   // bottom-right   
};

const GLint EDGE_KERNEL[9]{
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1
};

const GLfloat BLUR_KERNEL[9]{
    1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
    2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
    1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
};
