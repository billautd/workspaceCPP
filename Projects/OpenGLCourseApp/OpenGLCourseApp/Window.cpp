#include "Window.h"

Window::Window() : width(WINDOW_WIDTH), height(WINDOW_HEIGHT) {}

Window::Window(GLuint cWidth, GLuint cHeight) : width(cWidth), height(cHeight) {}

int Window::Init() {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
		SDL_Quit();
		return 1;
	}

	//SDL_ttf init
	if (TTF_Init() != 0) {
		std::cerr << "Error initializing TTF.\n";
		SDL_Quit();
		return 1;
	}

	//Set backup OpenGl version to 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Set OpenGL profile to Core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Window init
	mainWindow = SDL_CreateWindow(
		"OpenGL Course App",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	if (!mainWindow) {
		std::cerr << "Error initializing SDL window.\n";
		SDL_Quit();
		return 1;
	}

	//Create OpenGL Context
	void* mainContext{ SDL_GL_CreateContext(mainWindow) };
	if (mainContext == nullptr) {
		std::cerr << "Error initializing OpenGL context.\n";
		SDL_Quit();
		return 1;
	}
	SDL_GL_MakeCurrent(mainWindow, mainContext);

	SDL_ShowCursor(SDL_DISABLE);

	//Init GLAD
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "Error initializing GLAD.\n";
		SDL_Quit();
		return 1;
	}

	//Viewport
	glViewport(0, 0, width, height);

	//Fill or Line
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Depth buffer
	glEnable(GL_DEPTH_TEST);

	return 0;
}

void Window::GLClear() {
	//Render BG color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

