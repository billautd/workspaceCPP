#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::textures2D{};
std::map<std::string, Shader> ResourceManager::shaders{};


Shader& ResourceManager::LoadShader(const std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Texture2D& ResourceManager::LoadTexture2D(const std::string name, const char* file, const bool alpha)
{
    textures2D[name] = LoadTextureFromFile(file, alpha);
    return textures2D[name];
}

void ResourceManager::Clear()
{
    for (const auto& shaderIt : shaders) 
        glDeleteProgram(shaderIt.second.id);
    
    for (const auto& texture2DIt : textures2D)
        glDeleteTextures(1, &texture2DIt.second.id);

    shaders.clear(); 
    textures2D.clear();
}

Shader& ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    //Retrieve vertex and fragment source code from file path
    std::string vertexCode{};
    std::string fragmentCode{};
    std::string geometryCode{};
    try {
        //Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream{};
        std::stringstream fShaderStream{};

        //Read file buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        //Close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        //Do the same for geometry shader if present
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cerr << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const char* vShaderCode{ vertexCode.c_str() };
    const char* fShaderCode{ fragmentCode.c_str() };
    const char* gShaderCode{ geometryCode.c_str() };

    //Complete shader object with given code
    Shader* shader{ new Shader() };
    shader->Compile(vShaderCode, fShaderCode, gShaderFile == nullptr ? nullptr : gShaderCode);
    return *shader;
}

Texture2D& ResourceManager::LoadTextureFromFile(const char* file, const bool alpha)
{
    //Create texture object
    Texture2D* texture{ new Texture2D() };
    texture->internalFormat = alpha ? GL_RGBA : GL_RGB;
    texture->imageFormat = alpha ? GL_RGBA : GL_RGB;

    //Load image
    int width{};
    int height{};
    int nbrChannels{};
    unsigned char* data = stbi_load(file, &width, &height, &nbrChannels, 0);

    if (data) 
        texture->Generate(width, height, data);
    else 
        std::cerr << "ERROR::TEXTURE2D: Failed to read texture data" << std::endl;

    stbi_image_free(data);
    return *texture;
}
