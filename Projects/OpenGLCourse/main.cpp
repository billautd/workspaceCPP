#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "glfw3.h"
#include <map>
#include <iostream>
#include "Shader.h"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"
#include "Constants.h"
#include "AssetManager.h"

GLuint vaoCube, vboCube, vaoFloor, vboFloor, vaoSquareVertical, vboSquareVertical, vaoSquare, vboSquare, vaoSkybox, vboSkybox;
GLuint fbo, rbo, textureColorBuffer;
Shader* mainShader{ nullptr };
Shader* singleColorShader{ nullptr };
Shader* modelShader{ nullptr };
Shader* outlineShader{ nullptr };
Shader* textureShader{ nullptr };
Shader* grassShader{ nullptr };
Shader* fboShader{ nullptr };
Shader* skyboxShader{ nullptr };

std::vector<Shader*> shaders;
std::vector<GLuint> vaos;
std::vector<GLuint> vbos;

Camera camera{};
GLFWwindow* window{ nullptr };
AssetManager* assetManager{ new AssetManager() };

GLfloat lastX{ WINDOW_WIDTH / 2.0f };
GLfloat lastY{ WINDOW_HEIGHT / 2.0f };
GLboolean firstMouse{ true };
GLfloat yaw{ -90.0f };
GLfloat pitch{};

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = static_cast<GLfloat>(xpos);
		lastY = static_cast<GLfloat>(ypos);
		firstMouse = false;
	}
	const GLfloat sensitivity{ 0.1f };
	GLfloat xOffset{ static_cast<GLfloat>(sensitivity * (xpos - lastX)) };
	GLfloat yOffset{ static_cast<GLfloat>(sensitivity * (lastY - ypos)) };
	lastX = static_cast<GLfloat>(xpos);
	lastY = static_cast<GLfloat>(ypos);

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<GLfloat>(yoffset));
}

void ProcessInput(GLFWwindow* window, const GLfloat deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovementEnum::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovementEnum::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovementEnum::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovementEnum::RIGHT, deltaTime);
}

void LoadAssets() {
	//Load textures
	assetManager->AddTexture("woodenContainer", AssetManager::GenerateTexture("woodenContainer.jpg", "./Assets"));
	assetManager->AddTexture("awesomeFace", AssetManager::GenerateTexture("awesomeFace.png", "./Assets"));
	assetManager->AddTexture("steelContainerDiffuse", AssetManager::GenerateTexture("steelContainerDiffuse.png", "./Assets"));
	assetManager->AddTexture("steelContainerSpecular", AssetManager::GenerateTexture("steelContainerSpecular.png", "./Assets"));
	assetManager->AddTexture("transparentWindow", AssetManager::GenerateTexture("transparentWindow.png", "./Assets"));
	assetManager->AddTexture("marble", AssetManager::GenerateTexture("marble.jpg", "./Assets"));
	assetManager->AddTexture("grass", AssetManager::GenerateTexture("grass.png", "./Assets", GL_CLAMP_TO_EDGE));

	const std::vector<std::string> faces {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};
	stbi_set_flip_vertically_on_load(false);
	assetManager->AddCubeMap("skybox", AssetManager::GenerateCubeMap(faces, "./Assets/skybox", GL_CLAMP_TO_EDGE));
	stbi_set_flip_vertically_on_load(true);


	//Load models
	assetManager->AddModel("backpack", AssetManager::GenerateModel("backpack.obj", "./Assets/backpack"));
}

void CreateShaders() {
	//Configure shader
	mainShader = new Shader(std::string("./Shaders/vertex3D.shader").c_str(), std::string("./Shaders/fragment3D.shader").c_str());
	singleColorShader = new Shader(std::string("./Shaders/vertex3D.shader").c_str(), std::string("./Shaders/fragmentSingleColor.shader").c_str());
	modelShader = new Shader(std::string("./Shaders/vertex3D.shader").c_str(), std::string("./Shaders/fragmentModel.shader").c_str());
	outlineShader = new Shader(std::string("./Shaders/vertex3D.shader").c_str(), std::string("./Shaders/fragmentOutline.shader").c_str());
	textureShader = new Shader(std::string("./Shaders/vertex2D.shader").c_str(), std::string("./Shaders/fragment2D.shader").c_str());
	grassShader = new Shader(std::string("./Shaders/vertex2D.shader").c_str(), std::string("./Shaders/fragmentGrass.shader").c_str());
	fboShader = new Shader(std::string("./Shaders/vertexFBO.shader").c_str(), std::string("./Shaders/fragmentFBO.shader").c_str());
	skyboxShader = new Shader(std::string("./Shaders/vertexSkybox.shader").c_str(), std::string("./Shaders/fragmentSkybox.shader").c_str());

	shaders = { mainShader, singleColorShader, modelShader, outlineShader, textureShader, grassShader, fboShader, skyboxShader };
}

void ConfigureVAOVBO() {
	glGenVertexArrays(1, &vaoCube);
	glGenBuffers(1, &vboCube);

	glBindVertexArray(vaoCube);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboCube);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);

	glGenVertexArrays(1, &vaoFloor);
	glGenBuffers(1, &vboFloor);
	glBindVertexArray(vaoFloor);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboFloor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glGenVertexArrays(1, &vaoSquareVertical);
	glGenBuffers(1, &vboSquareVertical);
	glBindVertexArray(vaoSquareVertical);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboSquareVertical);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerticalVertices), squareVerticalVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glGenVertexArrays(1, &vaoSquare);
	glGenBuffers(1, &vboSquare);
	glBindVertexArray(vaoSquare);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboSquare);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);

	glGenVertexArrays(1, &vaoSkybox);
	glGenBuffers(1, &vboSkybox);
	glBindVertexArray(vaoSkybox);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboSkybox);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	}
	glBindVertexArray(0);

	vaos = { vaoCube, vaoFloor, vaoSquareVertical, vaoSquare, vaoSkybox };
	vbos = { vboCube, vboFloor, vboSquareVertical, vboSquare, vboSkybox };
}

void Clear() {
	for (GLuint vao : vaos)
		glDeleteVertexArrays(1, &vao);
	for (GLuint vbo : vbos)
		glDeleteBuffers(1, &vbo);
	for (Shader* shader : shaders)
		shader->Delete();

	glfwTerminate();
}

void DisplaySkybox() {
	glDepthMask(GL_FALSE);

	skyboxShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, assetManager->GetCubeMap("skybox"));

	//Uniforms
	skyboxShader->SetInt("skybox", 0);

	//MVP
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetCameraView()));

	skyboxShader->SetMat4("view", view);
	skyboxShader->SetMat4("projection", camera.GetCameraProjection());

	glBindVertexArray(vaoSkybox);
	{
		glDrawArrays(GL_TRIANGLES, 0, sizeof(skyboxVertices) / sizeof(GLfloat));
	}
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

void DisplayGrass() {
	//Face culling
	glDisable(GL_CULL_FACE);

	grassShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("grass"));

	//Uniforms
	grassShader->SetInt("textureSampler", 0);

	//MVP
	grassShader->SetMat4("view", camera.GetCameraView());
	grassShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindVertexArray(vaoSquareVertical);
	{
		for (const glm::vec3 pos : grassPositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pos);
			textureShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(squareVerticalVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayWindows() {
	//Face culling
	glDisable(GL_CULL_FACE);

	textureShader->Use();

	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("transparentWindow"));

	//Uniforms
	textureShader->SetInt("textureSampler", 0);

	//MVP
	textureShader->SetMat4("view", camera.GetCameraView());
	textureShader->SetMat4("projection", camera.GetCameraProjection());


	//Sort to display furthest from camera first and closest last
	std::map<GLfloat, glm::vec3> sorted;
	for (const glm::vec3 pos : windowsPositions) {
		GLfloat distance{ glm::length(camera.GetPosition() - pos) };
		sorted.emplace(distance, pos);
	}

	glm::mat4 model{ glm::mat4(1.0f) };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindVertexArray(vaoSquareVertical);
	{
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			textureShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(squareVerticalVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayFloor() {
	//Face culling
	glEnable(GL_CULL_FACE);

	textureShader->Use();
	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("marble"));

	//Uniforms
	textureShader->SetInt("textureSampler", 0);

	//MVP
	textureShader->SetMat4("view", camera.GetCameraView());
	textureShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoFloor);
	{
		textureShader->SetMat4("model", model);

		//Render
		glDrawArrays(GL_TRIANGLES, 0, sizeof(floorVertices) / sizeof(GLfloat));
	}
	glBindVertexArray(0);
}

void DisplayNormalCubes() {
	//Face culling
	glEnable(GL_CULL_FACE);

	mainShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("steelContainerDiffuse"));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("steelContainerSpecular"));

	//Uniforms
	mainShader->SetInt("material.diffuse", 0);
	mainShader->SetInt("material.specular", 1);
	mainShader->SetFloat("material.shininess", 64.0f);
	mainShader->SetDirLight(dirLight, "dirLight");
	mainShader->SetPointLight(pointLight0, "pointLights[0]");
	mainShader->SetPointLight(pointLight1, "pointLights[1]");
	mainShader->SetPointLight(pointLight2, "pointLights[2]");
	mainShader->SetPointLight(pointLight3, "pointLights[3]");
	mainShader->SetVec3("viewPos", camera.GetPosition());

	//MVP
	mainShader->SetMat4("view", camera.GetCameraView());
	mainShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoCube);
	{
		for (const glm::vec3 position : cubePositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, static_cast<GLfloat>(glfwGetTime()) * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			mainShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayOutlineCubes() {
	//Face culling
	glDisable(GL_CULL_FACE);

	outlineShader->Use();

	//MVP
	outlineShader->SetMat4("view", camera.GetCameraView());
	outlineShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoCube);
	{
		for (const glm::vec3 position : cubePositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::scale(model, glm::vec3(1.1f));
			model = glm::rotate(model, static_cast<GLfloat>(glfwGetTime()) * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			outlineShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayLightCubes() {
	//Face culling
	glEnable(GL_CULL_FACE);

	singleColorShader->Use();
	//Uniforms

	singleColorShader->SetVec3("color", glm::vec3(1.0f));

	//MVP
	singleColorShader->SetMat4("view", camera.GetCameraView());
	singleColorShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoCube);
	{
		for (const glm::vec3 position : pointLightPositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			singleColorShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayModels() {
	modelShader->Use();
	//Uniform
	//LIGHTS
	modelShader->SetVec3("viewPos", camera.GetPosition());
	modelShader->SetPointLight(pointLight0, "pointLights[0]");
	modelShader->SetPointLight(pointLight1, "pointLights[1]");
	modelShader->SetPointLight(pointLight2, "pointLights[2]");
	modelShader->SetPointLight(pointLight3, "pointLights[3]");

	//MVP
	modelShader->SetMat4("view", camera.GetCameraView());
	modelShader->SetMat4("projection", camera.GetCameraProjection());

	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, modelPosition);
	modelShader->SetMat4("model", model);

	for (const Model* modelContent : assetManager->GetModels())
		modelContent->Draw(*modelShader);
}

void CreateFBORBO() {
	//Framebuffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	{
		//Generate texture to attach to framebuffer
		glGenTextures(1, &textureColorBuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		//Attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

		//Renderbuffer to attach to framebuffer
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT);
		}

		//Attach renderbuffer to framebuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::FRAMEBUFFER : Framebuffer is not complete\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderFBOTexture() {
	glDisable(GL_DEPTH_TEST);
	fboShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);

	fboShader->SetInt("textureSampler", 0);
	glBindVertexArray(vaoSquare);
	{
		glDrawArrays(GL_TRIANGLES, 0, sizeof(squareVertices) / sizeof(GLfloat));
	}
	glBindVertexArray(0);
}

void DrawScene() {
	DisplaySkybox();

	glStencilMask(0x00);
	DisplayFloor();

	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xff);
	DisplayNormalCubes();

	glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	DisplayOutlineCubes();


	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilMask(0xff);
	glEnable(GL_DEPTH_TEST);
	DisplayLightCubes();

	DisplayModels();
	DisplayGrass();
	DisplayWindows();
}

int Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create GLFW Window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == nullptr) {
		std::cerr << "ERROR::WINDOW : Failed to create GLFW Window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "ERROR::GLAD : Failed to initialize GLAD\n";
		glfwTerminate();
		return -1;
	}

	//Depth testing
	glEnable(GL_DEPTH_TEST);
	//Stencil testing
	glEnable(GL_STENCIL_TEST);
	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Flip textures
	stbi_set_flip_vertically_on_load(true);

	//Mouse input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	//Viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	return 0;
}

int main(int argc, char** argv) {
	int initSuccess{ Init() };
	if (initSuccess != 0)
		return initSuccess;

	//Init and config
	CreateShaders();
	ConfigureVAOVBO();
	LoadAssets();
	CreateFBORBO();

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		//Delta time
		GLfloat deltaTime{ 0.0f }; // Time between current frame and last frame
		GLfloat lastFrame{ 0.0f }; //Time of last frame

		GLfloat currentFrame{ static_cast<GLfloat>(glfwGetTime()) };
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input
		ProcessInput(window, deltaTime);

		//Render
		//First pass
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		DrawScene();

		//Second pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
		RenderFBOTexture();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Clear();

	return 0;
}

