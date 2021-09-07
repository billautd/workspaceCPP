#include "ShaderManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string,Shader> ShaderManager::shaders{};

const Shader& ShaderManager::LoadShaderFromPath(const std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    std::string vShaderString;
    std::string fShaderString;
    std::string gShaderString;

    //Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        //Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        //Read from files
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        vShaderString = vShaderStream.str();
        fShaderString = fShaderStream.str();

        if (geometryPath != nullptr) {
            std::ifstream gShaderFile;
            gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            gShaderString = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e) {
        std::stringstream errorString;
        errorString << "Error trying to create shader at " << vertexPath << " & " << fragmentPath;
        if (geometryPath != nullptr) 
            errorString << " & " << geometryPath;
        errorString << '\n' << "|_" << '\n' ;

        std::cerr << errorString.str();
    }

    const Shader& shader{ LoadShader(vertexPath, vShaderString.c_str(), fragmentPath, fShaderString.c_str(), geometryPath, gShaderString.c_str()) };
    shaders[name] = shader;
    return shader;
}

const Shader& ShaderManager::LoadShader(const char* vertexPath, const char* vertexSource,
    const char* fragmentPath, const char* fragmentSource,
    const char* geometryPath, const char* geometrySource) {
    Shader* shader{new Shader()};

    unsigned int sVertex, sFragment, gShader;

    // Vertex shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileErrors(sVertex, "VERTEX", vertexSource);

    // Fragment shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileErrors(sFragment, "FRAGMENT", fragmentSource);

    // If geometry shader source code is given, also compile geometry shader
    if (geometryPath != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        CheckCompileErrors(gShader, "GEOMETRY", geometrySource);
    }

    // Shader program
    shader->id = glCreateProgram();
    glAttachShader(shader->id, sVertex);
    glAttachShader(shader->id, sFragment);
    if (geometryPath != nullptr)
        glAttachShader(shader->id, gShader);
    glLinkProgram(shader->id);
    CheckCompileErrors(shader->id, "PROGRAM", nullptr);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometryPath != nullptr)
        glDeleteShader(gShader);

    return *shader;
}

void ShaderManager::CheckCompileErrors(const GLuint object, const std::string type, const char* path)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "  | ERROR::SHADER AT " << path << ": Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "  | ERROR::Shader: Link - time error : Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}