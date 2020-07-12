#ifndef GAME_H
#define GAME_H

#include <random>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Controller; // Forward declaration

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Controller &controller,
       Renderer &renderer);
  bool Run(std::size_t target_frame_duration);
  void EndGame() {_running = false; _pSnake->KillSnake();}
  void RestartGame() {_restart = true; _pSnake->KillSnake();}
  int GetScore() const;
  int GetSize() const;

 private:
  std::unique_ptr<Snake> _pSnake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();

  Controller &_controller;
  Renderer &_renderer;

  bool _running{true};
  bool _restart{false};
};

#endif