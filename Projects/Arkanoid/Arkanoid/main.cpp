#include "Game.h"

Game game{};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            game.keys[key] = true;
        else if (action == GLFW_RELEASE)
            game.keys[key] = false;
    }
}

int main() {
    //Init game
    game.Init();
    glfwSetFramebufferSizeCallback(game.window, FramebufferSizeCallback);
    glfwSetKeyCallback(game.window, KeyCallback);

    //DeltaTime
    GLfloat deltaTime{ 0.0f };
    GLfloat lastFrame{ 0.0f };

    while (!glfwWindowShouldClose(game.window)) {
        //Calc delta time
        GLfloat currentFrame{ static_cast<GLfloat>(glfwGetTime()) };
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        game.ProcessInput(deltaTime);
        game.Update(deltaTime);

        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        glfwSwapBuffers(game.window);
    }

    game.Clear();
    glfwTerminate();
	return 0;
}