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

GLuint vertexNumber{ 36 };
GLfloat vertices[] = {
	// x      y     z     texX  texY
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,     //front
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,     //top
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,    //back
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    //bottom
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    //left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    //right
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
};


GLshort indices[] = {
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
	int windowInitStatus = mainWindow->Init();
	int shadersInitStatus = InitShaders();

	GenerateVertexData();
	GenerateTextureData();
	if (windowInitStatus + shadersInitStatus == 0)
		isRunning = true;
}

int Game::InitShaders() {
	if (shader.Init("Shaders/vertex.shader", "Shaders/fragment.shader") != 0) {
		std::cerr << "Error while initializing shaders\n";
		return 1;
	};
	return 0;
}

void Game::GenerateVertexData() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	{
		//VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		//Color, texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void Game::FreeShaders() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader.GetProgramID());
}

//TODO Maybe find a way to make it more flexible
void Game::GenerateTextureData() {
	Texture::SetTextureWrap(GL_REPEAT);
	Texture::SetTextureFilter(GL_LINEAR);
	Texture wallTexture{};
	if (wallTexture.Init("Assets/Textures/wall.jpg") != 0) {
		std::cerr << "Error while initializing wall texture\n";
		return;
	}

	glGenTextures(1, &textureIds.at(0));
	glBindTexture(GL_TEXTURE_2D, textureIds.at(0));
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallTexture.GetWidth(),
			wallTexture.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, wallTexture.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture faceTexture{};
	stbi_set_flip_vertically_on_load(true);
	if (faceTexture.Init("Assets/Textures/awesomeface.png") != 0) {
		std::cerr << "Error while initializing face texture\n";
		return;
	}
	glGenTextures(1, &textureIds.at(1));
	glBindTexture(GL_TEXTURE_2D, textureIds.at(1));
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, faceTexture.GetWidth(),
			faceTexture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTexture.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	//Free textures
	wallTexture.FreeImage();
	faceTexture.FreeImage();
}

//TODO Maybe find a way to make it more flexible
void Game::BindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIds.at(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureIds.at(1));

	shader.SetInt("textureUnit1", 0);
	shader.SetInt("textureUnit2", 1);
}


void Game::ProcessInput(SDL_Event& e) {
	//Delta time
	Uint32 timeToWait{ FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame) };
	if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);

	//Delta time is the difference in seconds from the last frame
	GLfloat deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };

	//Clamp delta time to a max value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//Set the new ticks at the current frame for the next pass
	ticksLastFrame = SDL_GetTicks();

	//Set new cameraSpeed
	camera->SetSpeed(camera->GetSpeed()*deltaTime);

	if (e.type == SDL_WINDOWEVENT) {
		switch (e.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				glViewport(0, 0, e.window.data1, e.window.data2);
				break;
		}
	}

	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				isRunning = false;
				SDL_Quit();
				break;
			case SDLK_z:
				glm::vec3 newPosition = camera->GetPosition() + speed*camera->GetDirection();
				camera->SetPosition(newPosition);
				break;
			case SDLK_s:
				glm::vec3 newPosition = -1.0f*(camera->GetPosition() + speed*camera->GetDirection());
				camera->SetPosition(newPosition);
				break;
			case SDLK_q:
				glm::vec3 newPosition = -1.0f*(camera->GetPosition() + speed*camera->GetRight());
				camera->SetPosition(newPosition);
				break;
			case SDLK_d:
				glm::vec3 newPosition = camera->GetPosition() + speed*camera->GetRight();
				camera->SetPosition(newPosition);
				break;
		}
	}

	if (e.type == SDL_QUIT) {
		isRunning = false;
		SDL_Quit();
	}

}

void Game::MVP() {
	//View
	GLfloat radius{ 10.0f };
	glm::mat4 view = glm::mat4(1.0f);
	GLfloat camX = sin(SDL_GetTicks() / 1000.0f) * radius;
	GLfloat camZ = cos(SDL_GetTicks() / 1000.0f) * radius;
	camera->SetPosition(glm::vec3(camX, 0.0f, camZ));
	camera->LookAtCurrent(&view);
	shader.SetMat4f("view", view);


	//Projection
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), ASPECT_RATIO, 0.1f, 100.0f);
	shader.SetMat4f("projection", projection);

	glBindVertexArray(VAO);
	{
		//Model
		for (GLsizei i = 0; i < cubeNumbers; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			if (i % 3 == 0)
				model = glm::rotate(model, SDL_GetTicks() / 1000.0f, glm::vec3(0.5f, 1.0f, 0.0f));
			shader.SetMat4f("model", model);
			//glDrawArrays(GL_TRIANGLES, 0, vertexNumber);
			glDrawElements(GL_TRIANGLES, vertexNumber, GL_UNSIGNED_SHORT, 0);
		}
	}
	glBindVertexArray(0);
}
