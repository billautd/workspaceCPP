#include "glad/glad.h"
#include "Game.h"
#include <iostream>
#include "ShaderManager.h"
#include "Textures2DManager.h"

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

    // Glad : load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    //OpenGL config
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC1_COLOR, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void Game::Init()
{
    const GLint initStatus{ InitGL() };
    if (initStatus != 0) {
        std::cerr << "Error initialising OpenGL\n";
    }
}

void Game::ProcessInput(const GLfloat dt) const
{
    return void();
}

void Game::Update(const GLfloat dt) const
{
    return void();
}

void Game::Render() const
{
    return void();
}

void Game::Clear() const
{
    ShaderManager::Clear();
    Textures2DManager::Clear();
}
