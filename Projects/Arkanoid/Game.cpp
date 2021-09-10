#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
	delete spriteRenderer;
	glfwTerminate();
}

const int Game::InitGL() {
	//Init GLFW
	int success{ 0 };
	if (!(success = glfwInit())) {
		std::cerr << "ERROR::GLFW : Failed to initialize GLFW" << std::endl;
		return success;
	}
	//Using OpenGL 4.3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(width, height, "Arkanoid", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//Init GLAD
	if (!(success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
	{
		std::cout << "ERROR::GLAD : Failed to initialize GLAD" << std::endl;
		return success;
	}

	//Init OpenGL
	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return success;
}

void Game::Init() {
	//Shaders
	Shader& spriteShader{ ResourceManager::LoadShader("texture", "./Shaders/Vertex/vertexSprite.shader", "./Shaders/Fragment/fragmentSprite.shader") };
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f) };
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);

	//Textures
	spriteRenderer = new SpriteRenderer(spriteShader);
	ResourceManager::LoadTexture2D("face", "./Assets/face.png", true);

}

void Game::ProcessInput(const GLfloat dt) {

}

void Game::Update(const GLfloat dt) {

}

void Game::Render() {
	spriteRenderer->DrawSprite(ResourceManager::GetTexture2D("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}