#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"


SpriteRenderer  *Renderer;

Game::Game(unsigned int width, unsigned int height)
  : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {

}

void Game::Init() {
  ResourceManager::LoadShader("resources/shaders/vertexShader.vs", "resources/shaders/fragmentShader.fs", "sprite");
  
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("sprite").use().setInt("image", 0, true);
  ResourceManager::getShader("sprite").use().setMat4("projection", projection, true);

  // set render-specific controls
  Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
  // load textures
  ResourceManager::LoadTexture("resources/awesomeface.png", true, "face");
}

void Game::ProcessInput(float dt) {

}

void Game::Update(float dt) {

}

void Game::Render() {
    Renderer->DrawSprite(ResourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}