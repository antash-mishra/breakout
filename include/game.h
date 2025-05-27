#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <glm/gtc/matrix_transform.hpp>

enum GameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game {
  public:
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels etc.)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    
};

#endif