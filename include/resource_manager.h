#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "texture.h"
#include "shader.h"

class ResourceManager {
  public:
    // resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    // load shader program
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name);
    // get shader program
    static Shader getShader(std::string name);

    // load texture program
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
    // get texture
    static Texture2D getTexture(std::string name);

    // de-allocate all resources
    static void Clear();
  private:
    ResourceManager() {}

    // load shader from file
    static Shader loadShaderFromFile(const char *vTextureFile, const char *fShaderFile);
    // load texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};


#endif
