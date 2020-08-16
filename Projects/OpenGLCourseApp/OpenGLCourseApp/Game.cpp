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

void CalcAverageNormals(GLfloat vertices[], GLuint verticesNumber, GLshort indices[], GLuint indicesNumber, GLuint vLength, GLuint normalOffset) {
	for (size_t i = 0; i < indicesNumber; i += 3) {
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
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
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


GLuint indicesNumber{ 36 };
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

	CalcAverageNormals(vertices, verticesNumber, indices, indicesNumber, 8, 3);
	GenerateVertexData();
	GenerateTextureData();
	if (windowInitStatus + shadersInitStatus == 0)
		isRunning = true;
}

int Game::InitShaders() {
	if (lightSourceShader.Init("Shaders/LightSource/vertex.shader", "Shaders/LightSource/fragment.shader") != 0) {
		std::cerr << "Error while initializing light source shader\n";
		return 1;
	};

	if (containerShader.Init("Shaders/Container/vertex.shader", "Shaders/Container/fragment.shader") != 0) {
		std::cerr << "Error while initializing container shader\n";
		return 1;
	};
	return 0;
}

void Game::GenerateVertexData() {
	glGenVertexArrays(1, &containerVAO);
	glGenVertexArrays(1, &lightSourceVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Container
	glBindVertexArray(containerVAO);
	{
		//VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		//Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	//Light source
	glBindVertexArray(lightSourceVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void Game::FreeShaders() {
	glDeleteVertexArrays(1, &containerVAO);
	glDeleteVertexArrays(1, &lightSourceVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(lightSourceShader.GetProgramID());
	glDeleteProgram(containerShader.GetProgramID());
}

void Game::GenerateTextureData() {
	Texture::SetTextureWrap(GL_REPEAT);
	Texture::SetTextureFilter(GL_LINEAR);
	Texture containerTexture{ Texture() };
	if (containerTexture.Init("Assets/Textures/container.png", &textureIds.at(0), GL_RGBA) != 0) {
		std::cerr << "Error while initializing container texture\n";
		return;
	}

	Texture containerSpecularTexture{ Texture() };
	if (containerSpecularTexture.Init("Assets/Textures/container_specular.png", &textureIds.at(1), GL_RGBA) != 0) {
		std::cerr << "Error while initializing container specular texture\n";
		return;
	}

	Texture matrixTexture{ Texture() };
	if (matrixTexture.Init("Assets/Textures/matrix.jpg", &textureIds.at(2), GL_RGB) != 0) {
		std::cerr << "Error while initializing matrix texture\n";
		return;
	}

	containerShader.Use();
	containerShader.SetInt("material.diffuse", 0);
	containerShader.SetInt("material.specular", 1);
	containerShader.SetInt("material.emission", 2);

	//Free textures
	containerTexture.FreeImage();
	containerSpecularTexture.FreeImage();
	matrixTexture.FreeImage();

}

void Game::BindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIds.at(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureIds.at(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureIds.at(2));
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
	containerShader.Use();

	// directional light
	containerShader.SetVec3("dirLight.direction", 0.0f, 0.0f, -1.0f);
	containerShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	containerShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	containerShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	containerShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
	containerShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	containerShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	containerShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	containerShader.SetFloat("pointLights[0].constant", 1.0f);
	containerShader.SetFloat("pointLights[0].linear", 0.09f);
	containerShader.SetFloat("pointLights[0].quadratic", 0.032f);
	// point light 2
	containerShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
	containerShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	containerShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	containerShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	containerShader.SetFloat("pointLights[1].constant", 1.0f);
	containerShader.SetFloat("pointLights[1].linear", 0.09f);
	containerShader.SetFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	containerShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
	containerShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	containerShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	containerShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	containerShader.SetFloat("pointLights[2].constant", 1.0f);
	containerShader.SetFloat("pointLights[2].linear", 0.09f);
	containerShader.SetFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	containerShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
	containerShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	containerShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	containerShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	containerShader.SetFloat("pointLights[3].constant", 1.0f);
	containerShader.SetFloat("pointLights[3].linear", 0.09f);
	containerShader.SetFloat("pointLights[3].quadratic", 0.032f);
	// spotLight
	containerShader.SetVec3("spotLight.position", camera->GetPosition());
	containerShader.SetVec3("spotLight.direction", camera->GetDirection());
	containerShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	containerShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	containerShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	containerShader.SetFloat("spotLight.constant", 1.0f);
	containerShader.SetFloat("spotLight.linear", 0.09f);
	containerShader.SetFloat("spotLight.quadratic", 0.032f);
	containerShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	containerShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	containerShader.SetFloat("material.shininess", 2.0f);

	//View
	glm::mat4 view = camera->LookAtCurrent();
	containerShader.SetMat4f("view", view);

	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(camera->GetZoom()), ASPECT_RATIO, 0.1f, 100.0f);
	containerShader.SetMat4f("projection", projection);



	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(containerVAO);
	{
		//Model
		for (GLuint i = 0; i < cubeNumbers; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
			containerShader.SetMat4f("model", model);
			glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_SHORT, 0);
		}
	}
	glBindVertexArray(0);

	//Light source shader
	lightSourceShader.Use();
	lightSourceShader.SetVec3("lightColor", glm::vec3(1.0f));

	//View 
	view = camera->LookAtCurrent();
	lightSourceShader.SetMat4f("view", view);

	//Projection
	projection = glm::perspective(glm::radians(camera->GetZoom()), ASPECT_RATIO, 0.1f, 100.0f);
	lightSourceShader.SetMat4f("projection", projection);

	glBindVertexArray(containerVAO);
	{
		//Model
		for (GLuint i = 0; i < pointLightNumbers; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			lightSourceShader.SetMat4f("model", model);
			glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_SHORT, 0);
		}
	}
	glBindVertexArray(0);
}
