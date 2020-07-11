#ifndef SNAKE_H
#define SNAKE_H

#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <future>

#include "SDL.h"

class Game;  // forward declaration

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, Game *pGame)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        _pGame(pGame) {}

  std::future<void> Start(std::size_t);
  void Update(std::size_t);
  void GrowBody();
  void ChangeDirection(Direction);
  void IncreaseSpeed(float deltaSpd);
  bool SnakeCell(int x, int y);
  void KillSnake() {_alive = false;}
  bool IsAlive() const;
  void GetHead(int &x, int &y) const;
  std::vector<SDL_Point> GetBody() const;

  float speed{0.1f};
  int size{1};

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  bool _alive{true};
  float head_x;
  float head_y;
  Game *_pGame;  // Point to the game where Snake lives
  mutable std::shared_mutex _mtx;
  std::vector<SDL_Point> _body;
  Direction _direction = Direction::kUp;
  std::unordered_map<Direction, Direction> _oppositeDir{
      {Direction::kUp, Direction::kDown},
      {Direction::kDown, Direction::kUp},
      {Direction::kLeft, Direction::kRight},
      {Direction::kRight, Direction::kLeft}};
};

#endif