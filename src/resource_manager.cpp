#include "resource_manager.h"
#include "shader.h"
#include "texture.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

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
    // open file
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShaderStream, fShaderStream;

    // read file buffer content into stream
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();

    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    
  } catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader file" << std::endl;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // create hsader object
  Shader shader;
  shader.compile(vShaderCode, fShaderCode);
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

  // generate texture
  texture.Generate(width, height, data);
  // free image data
  stbi_image_free(data);
  return texture;
}
