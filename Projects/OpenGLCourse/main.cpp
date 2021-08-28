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
GLuint vaoLightCube, vboLightCube;
GLuint instancedGrassVBO;
GLuint fbo, rbo, textureColorBuffer;
GLuint uboPV, uboViewPos;
Shader* cubeShader{ nullptr };
Shader* lightCubeShader{ nullptr };
Shader* modelShader{ nullptr };
Shader* outlineShader{ nullptr };
Shader* textureShader{ nullptr };
Shader* grassShader{ nullptr };
Shader* fboShader{ nullptr };
Shader* skyboxShader{ nullptr };

std::vector<Shader*> shaders;
std::vector<GLuint> vaos;
std::vector<GLuint> vbos;
std::vector<GLuint> ubos;

Camera camera{};
GLFWwindow* window{ nullptr };
AssetManager* assetManager{ new AssetManager() };

GLfloat lastX{ WINDOW_WIDTH / 2.0f };
GLfloat lastY{ WINDOW_HEIGHT / 2.0f };
GLboolean firstMouse{ true };
GLfloat yaw{ -90.0f };
GLfloat pitch{};

//Can be increased a lot
const GLuint instancedGrassSize{ 2*10*10 };

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
	const std::string vertexPath{ "./Shaders/Vertex/" };
	const std::string fragmentPath{ "./Shaders/Fragment/" };

	//Configure shader
	cubeShader = new Shader(std::string(vertexPath + "vertexCube.shader").c_str(), std::string(fragmentPath + "fragmentCube.shader").c_str());
	lightCubeShader = new Shader(std::string(vertexPath + "vertexLightCube.shader").c_str(), std::string(fragmentPath +  "fragmentLightCube.shader").c_str());
	modelShader = new Shader(std::string(vertexPath + "vertexCube.shader").c_str(), std::string(fragmentPath + "fragmentModel.shader").c_str());
	outlineShader = new Shader(std::string(vertexPath + "vertexCube.shader").c_str(), std::string(fragmentPath + "fragmentOutline.shader").c_str());
	textureShader = new Shader(std::string(vertexPath + "vertexTexture.shader").c_str(), std::string(fragmentPath + "fragmentTexture.shader").c_str());
	grassShader = new Shader(std::string(vertexPath + "vertexGrass.shader").c_str(), std::string(fragmentPath + "fragmentGrass.shader").c_str());
	fboShader = new Shader(std::string(vertexPath + "vertexFBO.shader").c_str(), std::string(fragmentPath + "fragmentFBO.shader").c_str());
	skyboxShader = new Shader(std::string(vertexPath + "vertexSkybox.shader").c_str(), std::string(fragmentPath + "fragmentSkybox.shader").c_str());

	shaders = { cubeShader, lightCubeShader, modelShader, outlineShader, textureShader, grassShader, fboShader, skyboxShader };
}

void ConfigureBufferObjects() {
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

	glGenVertexArrays(1, &vaoLightCube);
	glGenBuffers(1, &vboLightCube);
	glBindVertexArray(vaoLightCube);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboLightCube);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

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
		glGenBuffers(1, &instancedGrassVBO);
	glBindVertexArray(vaoSquareVertical);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboSquareVertical);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerticalVertices), squareVerticalVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Grass arrays
		std::vector<glm::mat4> displacements{ std::vector<glm::mat4>(instancedGrassSize) };
		const GLint numberPerLine{ static_cast<GLint>(sqrtf(instancedGrassSize/2.0f)/2.0f) };
		GLuint offset{ 0 };
		for (GLint i{ -numberPerLine }; i < numberPerLine; i++) {
			for (GLint j{ -numberPerLine }; j < numberPerLine; j++) {
				//Translation
				displacements.at(offset++) = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j));
				//Translation + rotation by 90
				displacements.at(offset++) = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, j)), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, instancedGrassVBO);
		glBufferData(GL_ARRAY_BUFFER, instancedGrassSize * sizeof(glm::mat4), &displacements.at(0), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2*sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3*sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
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

	//Uniform buffer object for matrices projection and view
	glGenBuffers(1, &uboPV);
	glBindBuffer(GL_UNIFORM_BUFFER, uboPV);
	{
		glBufferData(GL_UNIFORM_BUFFER, 2* sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//Bind to binding point 0
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboPV);


	//Uniform buffer object for camera position
	glGenBuffers(1, &uboViewPos);
	glBindBuffer(GL_UNIFORM_BUFFER, uboViewPos);
	{
		glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//Bind to binding point 1
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboViewPos);


	vaos = { vaoCube, vaoFloor, vaoSquareVertical, vaoSquare, vaoSkybox, vaoLightCube };
	vbos = { vboCube, vboFloor, vboSquareVertical, vboSquare, vboSkybox, vboLightCube };
	ubos = { uboPV, uboViewPos };
}

void UpdateUBOs() {
	//Update projection and view
	glBindBuffer(GL_UNIFORM_BUFFER, uboPV);
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.GetCameraProjection()));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.GetCameraView()));
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//Update camera position
	glBindBuffer(GL_UNIFORM_BUFFER, uboViewPos);
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(camera.GetPosition()));
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

void Clear() {
	for (GLuint vao : vaos)
		glDeleteVertexArrays(1, &vao);
	for (GLuint vbo : vbos)
		glDeleteBuffers(1, &vbo);
	for (GLuint ubo : ubos)
		glDeleteBuffers(1, &ubo);
	for (Shader* shader : shaders)
		shader->Delete();

	glfwTerminate();
}

void DisplayFloor() {
	textureShader->Use();
	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("marble"));

	//Uniforms
	textureShader->SetInt("textureSampler", 0);

	//Model
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
	cubeShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("steelContainerDiffuse"));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("steelContainerSpecular"));

	//Uniforms
	cubeShader->SetInt("material.diffuse", 0);
	cubeShader->SetInt("material.specular", 1);
	cubeShader->SetFloat("material.shininess", 64.0f);
	cubeShader->SetDirLight(dirLight, "dirLight");
	cubeShader->SetPointLight(pointLight0, "pointLights[0]");
	cubeShader->SetPointLight(pointLight1, "pointLights[1]");
	cubeShader->SetPointLight(pointLight2, "pointLights[2]");
	cubeShader->SetPointLight(pointLight3, "pointLights[3]");

	//Model
	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoCube);
	{
		for (const glm::vec3 position : cubePositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, static_cast<GLfloat>(glfwGetTime()) * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			cubeShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayOutlineCubes() {
	outlineShader->Use();

	//Model
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
	lightCubeShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, assetManager->GetCubeMap("skybox"));

	//Uniforms
	lightCubeShader->SetInt("skybox", 0);

	//Model
	glm::mat4 model{ glm::mat4(1.0f) };
	glBindVertexArray(vaoLightCube);
	{
		for (const glm::vec3 position : pointLightPositions) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			lightCubeShader->SetMat4("model", model);

			//Render
			glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / sizeof(GLfloat));
		}
	}
	glBindVertexArray(0);
}

void DisplayModels() {
	modelShader->Use();
	
	//Lights
	modelShader->SetPointLight(pointLight0, "pointLights[0]");
	modelShader->SetPointLight(pointLight1, "pointLights[1]");
	modelShader->SetPointLight(pointLight2, "pointLights[2]");
	modelShader->SetPointLight(pointLight3, "pointLights[3]");

	//Model
	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, modelPosition);
	modelShader->SetMat4("model", model);

	for (const Model* modelContent : assetManager->GetModels())
		modelContent->Draw(*modelShader);
}

void DisplayGrass() {
	grassShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("grass"));

	//Uniforms
	grassShader->SetInt("textureSampler", 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindVertexArray(vaoSquareVertical);
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(squareVerticalVertices) / sizeof(GLfloat), instancedGrassSize);
	}
	glBindVertexArray(0);
}

void DisplayWindows() {
	textureShader->Use();

	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, assetManager->GetTexture("transparentWindow"));

	//Uniforms
	textureShader->SetInt("textureSampler", 0);

	//Sort to display furthest from camera first and closest last
	std::map<GLfloat, glm::vec3> sorted;
	for (const glm::vec3 pos : windowsPositions) {
		GLfloat distance{ glm::length(camera.GetPosition() - pos) };
		sorted.emplace(distance, pos);
	}

	//Model
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

void DisplaySkybox() {
	skyboxShader->Use();

	//Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, assetManager->GetCubeMap("skybox"));

	//Uniforms
	skyboxShader->SetInt("skybox", 0);

	//Update view correctly to remove w value
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetCameraView()));
	skyboxShader->SetMat4("projection", camera.GetCameraProjection());
	skyboxShader->SetMat4("view", view);

	glBindVertexArray(vaoSkybox);
	{
		glDrawArrays(GL_TRIANGLES, 0, sizeof(skyboxVertices) / sizeof(GLfloat));
	}
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

void DrawScene() {

	glStencilMask(0x00);
	glEnable(GL_CULL_FACE);
	DisplayFloor();

	//glStencilFunc(GL_ALWAYS, 1, 0xff);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glStencilMask(0xff);
	DisplayNormalCubes();

	//glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	//glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	//DisplayOutlineCubes();

	glEnable(GL_CULL_FACE);
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilMask(0xff);
	glEnable(GL_DEPTH_TEST);
	DisplayLightCubes();

	DisplayModels();

	glDisable(GL_CULL_FACE);
	DisplayGrass();

	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	DisplaySkybox();
	glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);
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
	ConfigureBufferObjects();
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
		UpdateUBOs();
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

