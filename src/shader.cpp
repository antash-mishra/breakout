#include "shader.h"

#include <iostream>

Shader &Shader::use() {
  glUseProgram(this->ID);
  return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource) {
  unsigned int sVertex, sFragment;
  
  // vertex shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");

  // fragment shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");

  // shader program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, sVertex);
  glAttachShader(this->ID, sFragment);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");

  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

void Shader::setInt(const char* name, int value, bool useShader) {
  if (useShader)
    this->use();
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setFloat(const char* name, float value, bool useShader) {
  if (useShader)
    this->use();
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVec2f(const char* name, const glm::vec2 &value, bool useShader) {
  if (useShader)
    this->use();
  glUniform2fv(glGetUniformLocation(this->ID, name), 1, &value[0]);
}

void Shader::setVec2f(const char* name, float x, float y, bool useShader) {
  if (useShader)
    this->use();
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVec3f(const char* name, const glm::vec3 &value, bool useShader) {
  if (useShader)
    this->use();
  glUniform3fv(glGetUniformLocation(this->ID, name), 1, &value[0]);
}

void Shader::setVec3f(const char* name, float x, float y, float z, bool useShader) {
  if (useShader)
    this->use();
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVec4f(const char* name, const glm::vec4 &value, bool useShader) {
  if (useShader)
    this->use();
  glUniform4fv(glGetUniformLocation(this->ID, name), 1, &value[0]);
}

void Shader::setVec4f(const char* name, float x, float y, float z, float w, bool useShader) {
  if (useShader)
    this->use();
  glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::setMat2(const char* name, const glm::mat2 &mat, bool useShader) {
  if (useShader)
    this->use();
  glUniformMatrix2fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const char* name, const glm::mat3 &mat, bool useShader) {
  if (useShader)
    this->use();
  glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const char* name, const glm::mat4 &mat, bool useShader) {
  if (useShader)
    this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::PROGRAM of type " << type << " -- Link-time error: " << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}