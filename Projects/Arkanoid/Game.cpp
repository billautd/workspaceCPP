#include "glad/glad.h"
#include "Game.h"
#include <iostream>
#include "ShaderManager.h"
#include "Textures2DManager.h"


void Game::Init()
{
    const GLint initStatus{ InitGL() };
    if (initStatus != 0) {
        std::cerr << "Error initialising OpenGL\n";
        glfwTerminate();
    }

    LoadShaders();
    LoadAssets();
}

const GLint Game::InitGL()
{
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW\n";
        return -1;
    }
    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Window creation
    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arkanoid", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Error creating GLFW window\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Glad : load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    //OpenGL config
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void Game::LoadShaders() {
    //Load shaders
    const Shader& spriteShader{ ShaderManager::LoadShaderFromPath("sprite", "./Shaders/Vertex/vertexSprite.shader", "./Shaders/Fragment/fragmentSprite.shader", nullptr) };
    spriteRenderer = new SpriteRenderer(spriteShader);

    //Configure shaders
    glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f) };

    //Sprite
    spriteShader.Use();
    spriteShader.SetMat4("projection", projection);
    spriteShader.SetInt("image", 0);
}

void Game::LoadAssets() {
    Textures2DManager::Generate("face", "./Assets/face.png");
}


void Game::ProcessInput(const GLfloat dt)
{
}

void Game::Update(const GLfloat dt)
{
}

void Game::Render()
{
}

void Game::Clear()
{
    ShaderManager::Clear();
    Textures2DManager::Clear();

    delete spriteRenderer;
}
