#pragma once
#include "glad/glad.h"
#include "glm.hpp"
#include "Material.h"
#include "DirLight.h"
#include "PointLight.h"

const GLsizei WINDOW_HEIGHT{ 800 };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLsizei WINDOW_WIDTH{ static_cast<GLsizei>(ASPECT_RATIO * WINDOW_HEIGHT) };

const GLfloat squareVertices[]{
	// positions   // texture Coords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

const GLfloat squareVerticalVertices[]{
	// positions          // texture Coords
	 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-1.0f,  2.0f,  0.0f,  0.0f, 1.0f,

	 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-1.0f,  2.0f,  0.0f,  0.0f, 1.0f,
	 1.0f,  2.0f,  0.0f,  1.0f, 1.0f
};

const GLfloat floorVertices[]{
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 50.0f, 0.0f,  50.0f,  10.0f, 0.0f,
	-50.0f, 0.0f, -50.0f,  0.0f, 10.0f,
	-50.0f, 0.0f,  50.0f,  0.0f, 0.0f,

	 50.0f, 0.0f,  50.0f,  10.0f, 0.0f,
	 50.0f, 0.0f, -50.0f,  10.0f, 10.0f,
	-50.0f, 0.0f, -50.0f,  0.0f, 10.0f
};

const GLfloat cubeVertices[] = {
	//Vertex position      Texture    Normal
	// Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// Bottom-left
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom-right         
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,// bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,// top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,// bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// top-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,// bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,// top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,// bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// top-right
	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// top-left
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,// top-right         
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// top-left
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,// bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// top-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,// bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-left
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-right     
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f  // bottom-left        
};

const glm::vec3 cubePositions[]{
	glm::vec3(0.0f,  2.0f,  0.0f),
	glm::vec3(2.0f,  7.0f, -15.0f),
	glm::vec3(-1.5f, 5.2f, -2.5f),
	glm::vec3(-3.8f, 2.0f, -2.3f),
	glm::vec3(2.4f, 6.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, 5.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  3.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

const glm::vec3 grassPositions[]{
	glm::vec3(-2.5f,  0.0f, -4.48f),
	glm::vec3(5.5f,  0.0f,  6.51f),
	glm::vec3(-5.0f,  0.0f,  3.7f),
	glm::vec3(-6.3f,  0.0f, -2.3f),
	glm::vec3(2.5f,  0.0f, -1.6f)
};

const glm::vec3 windowsPositions[]{
	glm::vec3(-6.5f,  0.0f, -1.48f),
	glm::vec3(12.5f,  0.0f,  4.51f),
	glm::vec3(2.0f,  0.0f,  9.7f),
};

//LIGHTS
const std::vector<glm::vec3> pointLightPositions{
	glm::vec3(0.7f,  4.2f,  2.0f),
	glm::vec3(2.3f, 9.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  3.0f, -3.0f)
};

const DirLight dirLight{
	glm::vec3(-0.2f, -1.0f, 0.3f),
	glm::vec3(0.05f),
	glm::vec3(0.4f),
	glm::vec3(0.5f)
};

const PointLight pointLight0{
	pointLightPositions.at(0),
	glm::vec3(0.05f),
	glm::vec3(0.2f),
	glm::vec3(1.0f),
	1.0f,
	0.045f,
	0.0075f,
};

const PointLight pointLight1{
	pointLightPositions.at(1),
	glm::vec3(0.05f),
	glm::vec3(0.2f),
	glm::vec3(1.0f),
	1.0f,
	0.045f,
	0.0075f,
};

const PointLight pointLight2{
	pointLightPositions.at(2),
	glm::vec3(0.05f),
	glm::vec3(0.2f),
	glm::vec3(1.0f),
	1.0f,
	0.045f,
	0.0075f,
};

const PointLight pointLight3{
	pointLightPositions.at(3),
	glm::vec3(0.05f),
	glm::vec3(0.2f),
	glm::vec3(1.0f),
	1.0f,
	0.045f,
	0.0075f,
};

const glm::vec3 modelPosition{ 8.0f, 4.0f, -4.0f };