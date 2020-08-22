#include "Game.h"
#include "Model.h"

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

GLuint cubeVerticesNumber{ 24 };
GLfloat cubeVertices[] = {
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


GLuint cubeIndicesNumber{ 36 };
GLuint cubeIndices[] = {
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

GLuint planeVerticesNumber{ 6 };
GLfloat planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

GLuint squareVerticesNumber{ 6 };
GLfloat squareVertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

Game::~Game() {
	isRunning = false;
}

GLuint cubeVAO{ 0 };
GLuint cubeVBO{ 0 };
GLuint cubeEBO{ 0 };
GLuint planeVAO{ 0 };
GLuint planeVBO{ 0 };
GLuint grassVAO{ 0 };
GLuint grassVBO{ 0 };
GLuint cubeTexture{ 0 };
GLuint floorTexture{ 0 };
GLuint grassTexture{ 0 };
std::vector<glm::vec3> vegetation;


void Game::Init() {
	camera = new Camera();
	shader = new Shader();
	if (mainWindow->Init() != 0) {
		std::cerr << "Error while initializing SDLWindow\n";
		return;
	}
	if (shader->Init("Shaders/DepthTesting/vertex.shader", "Shaders/DepthTesting/fragment.shader") != 0) {
		std::cerr << "Error while initializing container shader\n";
		return;
	};
	isRunning = true;
	CalcAverageNormals(cubeVertices, cubeVerticesNumber, cubeIndices, cubeIndicesNumber, 8, 3);

	// cube VAO

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeEBO);
	glBindVertexArray(cubeVAO); {
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	// plane VAO

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO); {
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	glGenVertexArrays(1, &grassVAO);
	glGenBuffers(1, &grassVBO);
	glBindVertexArray(grassVAO); {
		glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	cubeTexture = Model::TextureFromFile("marble.jpg", "C:/Users/David/workspaceC++/Projects/OpenGLCourseApp/OpenGLCourseApp/Assets/Textures");
	floorTexture = Model::TextureFromFile("metal.png", "C:/Users/David/workspaceC++/Projects/OpenGLCourseApp/OpenGLCourseApp/Assets/Textures");
	grassTexture = Model::TextureFromFile("grass.png", "C:/Users/David/workspaceC++/Projects/OpenGLCourseApp/OpenGLCourseApp/Assets/Textures");

	shader->Use();
	shader->SetInt("texture1", 0);

	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
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

	shader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->LookAtCurrent();
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), ASPECT_RATIO, 0.1f, 100.0f);
	shader->SetMat4f("view", view);
	shader->SetMat4f("projection", projection);
	// cubes
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	shader->SetMat4f("model", model);
	glDrawElements(GL_TRIANGLES, cubeIndicesNumber, GL_UNSIGNED_INT, 0);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	shader->SetMat4f("model", model);
	glDrawElements(GL_TRIANGLES, cubeIndicesNumber, GL_UNSIGNED_INT, 0);
	// floor
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	shader->SetMat4f("model", glm::mat4(1.0f));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	//Grass
	glBindVertexArray(grassVAO);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	for (size_t i = 0; i < vegetation.size(); i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, vegetation.at(i));
		shader->SetMat4f("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
