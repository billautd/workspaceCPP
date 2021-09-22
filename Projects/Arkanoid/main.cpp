#include "Game.h"
#include <iostream>

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Game game{};

int main() {
	game.InitGL();
    game.Init();

	glfwSetKeyCallback(game.window, key_callback);
	glfwSetFramebufferSizeCallback(game.window, framebuffer_size_callback);

    GLfloat deltaTime{};
    GLfloat lastFrame{};

    while (!glfwWindowShouldClose(game.window)) {
        //Calculate delta time
        GLfloat currentFrame{ static_cast<GLfloat>(glfwGetTime()) };
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //ProcessInput
        game.ProcessInput(deltaTime);
        //Update game state
        game.Update(deltaTime);

        //Render
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        glfwSwapBuffers(game.window);
    }
    glfwTerminate();
    return 0;

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.keys[key] = true;
        else if (action == GLFW_RELEASE) {
            game.keys[key] = false;
            game.processedKeys[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}