#include "glad/glad.h"
#include "resource_manager.h"
#include "shader.h"
#include "texture.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "stb_image.h"

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name) {
  Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
  return Shaders[name];
}

Shader ResourceManager::getShader(std::string name) {
  return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name) {
  Textures[name] = loadTextureFromFile(file, alpha);
  return Textures[name];
}

Texture2D ResourceManager::getTexture(std::string name) {
  return Textures[name];
}

void ResourceManager::Clear() {
  // Delete all shaders
  for (auto iter: Shaders) {
    glDeleteProgram(iter.second.ID);
  }
  // Delete all textures
  for (auto iter: Textures) {
    glDeleteTextures(1, &iter.second.ID);
  }
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile) {
  std::string vertexCode;
  std::string fragmentCode;

  try {
    // Print current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      std::cout << "Current working directory: " << cwd << "\n";
    }
    
    std::cout << "Attempting to load shaders:\n";
    std::cout << "Vertex shader: " << vShaderFile << "\n";
    std::cout << "Fragment shader: " << fShaderFile << "\n";
    
    // open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);

    if (!vertexShaderFile.is_open()) {
      throw std::runtime_error(std::string("Failed to open vertex shader file: ") + vShaderFile);
    }
    if (!fragmentShaderFile.is_open()) {
      throw std::runtime_error(std::string("Failed to open fragment shader file: ") + fShaderFile);
    }

    std::cout << "Successfully opened shader files\n";
    std::stringstream vShaderStream, fShaderStream;

    // read file buffer content into streams
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();

    // convert streams into strings
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    if (vertexCode.empty()) {
      throw std::runtime_error(std::string("Vertex shader file is empty: ") + vShaderFile);
    }
    if (fragmentCode.empty()) {
      throw std::runtime_error(std::string("Fragment shader file is empty: ") + fShaderFile);
    }

    std::cout << "Successfully read shader contents\n";
    std::cout << "Vertex shader length: " << vertexCode.length() << " bytes\n";
    std::cout << "Fragment shader length: " << fragmentCode.length() << " bytes\n";
    
  } catch (const std::exception& e) {
    std::cout << "ERROR::SHADER: Failed to read shader files: " << e.what() << std::endl;
    throw; // Re-throw the exception to let the caller handle it
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  
  // create shader object
  Shader shader;
  shader.compile(vShaderCode, fShaderCode);
  std::cout << "Shader compilation completed\n";
  return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
  Texture2D texture;
  if(alpha) {
    texture.Internal_Format = GL_RGBA;
    texture.Image_Format = GL_RGBA;
  }

  // load image
  int width, height, nrChannels;
  unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

  std::cout << "Image loaded with dimensions: " << width << "x" << height << " and " << nrChannels << " channels\n";

  // generate texture
  texture.Generate(width, height, data);
  // free image data
  stbi_image_free(data);
  return texture;
}
