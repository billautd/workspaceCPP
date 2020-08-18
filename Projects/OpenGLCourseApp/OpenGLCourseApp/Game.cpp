#include "Game.h"

GLuint cubeNumbers{ 10 };
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLuint pointLightNumbers{ 4 };
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

GLuint verticesNumber{ 24 };
GLfloat vertices[] = {
	// x      y     z       nx     ny    nz      texX  texY
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 0.0f,     //front
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 0.0f,     //top
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 0.0f,    //back
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 1.0f,    //bottom
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 1.0f,    //left
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 1.0f,

	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 0.0f,    //right
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,    1.0f, 0.0f,
};

void CalcAverageNormals(GLfloat vertices[], GLuint verticesNumber, GLuint indices[], GLuint indicesNumber, GLuint vLength, GLuint normalOffset) {
	for (size_t i = 0; i < indicesNumber; i += 3) {
		GLuint in0 = indices[i] * vLength;
		GLuint in1 = indices[i + 1] * vLength;
		GLuint in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticesNumber / vLength; i++) {
		GLuint nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


GLuint indicesNumber{ 36 };
GLuint indices[] = {
	 0,  1,  2,   //front
	 2,  3,  0,

	 4,  5,  6,   //top
	 6,  7,  4,

	 8,  9, 10,   //back
	 10, 11,  8,

	 12, 13, 14,  //bottom
	 14, 15, 12,

	 16, 17, 18,  //left
	 18, 19, 16,

	 20, 21, 22,  //right
	 22, 23, 20,
};

Game::~Game() {
	isRunning = false;
}

void Game::Init() {
	camera = new Camera();
	shader = new Shader();
	if (mainWindow->Init() != 0) {
		std::cerr << "Error while initializing SDLWindow\n";
		return;
	}
	if (shader->Init("Shaders/Model/vertex.shader", "Shaders/Model/fragment.shader") != 0) {
		std::cerr << "Error while initializing container shader\n";
		return;
	};

	//CalcAverageNormals(vertices, verticesNumber, indices, indicesNumber, 8, 3);
	isRunning = true;
}




void Game::ProcessKeyboardInput(SDL_Event& e) {
	//Delta time
	GLuint timeToWait{ static_cast<GLuint>(FRAME_TARGET_TIME) - (SDL_GetTicks() - ticksLastFrame) };
	if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);

	//Delta time is the difference in seconds from the last frame
	GLfloat deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };

	//Clamp delta time to a max value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//Set the new ticks at the current frame for the next pass
	ticksLastFrame = SDL_GetTicks();



	if (e.type == SDL_WINDOWEVENT) {
		switch (e.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				glViewport(0, 0, e.window.data1, e.window.data2);
				break;
		}
	}

	if (e.type == SDL_QUIT) {
		isRunning = false;
		SDL_Quit();
		return;
	}

	camera->ProcessKeyboardInput(deltaTime);
}

void Game::ProcessMouseInput(SDL_Event& e) {
	GLint x{ 0 };
	GLint y{ 0 };
	SDL_GetMouseState(&x, &y);
	camera->ProcessMouseInput(e, x * 1.0f, y * 1.0f);
}

void Game::ProcessMouseScrollInput(SDL_Event& e) {
	if (e.type == SDL_MOUSEWHEEL)
		camera->ProcessMouseScrollInput(e.wheel.y * 2.0f);
}

void Game::MVP() {
	//Container shader
	shader->Use();

	//View
	glm::mat4 view = camera->LookAtCurrent();
	shader->SetMat4f("view", view);

	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), ASPECT_RATIO, 0.1f, 100.0f);
	shader->SetMat4f("projection", projection);


	//Model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	shader->SetMat4f("model", model);
}
