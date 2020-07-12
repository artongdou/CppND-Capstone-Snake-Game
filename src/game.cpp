#include "game.h"

#include <future>
#include <iostream>

#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height,
           Controller &controller, Renderer &renderer)
    : _pSnake(std::make_unique<Snake>(grid_width, grid_height, this)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      _controller(controller),
      _renderer(renderer) {
  _controller.SetSnake(_pSnake.get());
  _controller.SetGame(this);
  PlaceFood();
}

bool Game::Run(std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  auto fut_snake = _pSnake->Start(target_frame_duration);
  std::cout << "log: Snake has been spawned" << std::endl;
  // _controller.Start();

  while (_running && !_restart) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller.HandleInput();
    Update();
    _renderer.Render(_pSnake.get(), food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  std::cout << "log: Waiting for Snake to terminate" << std::endl;
  fut_snake.wait();
  std::cout << "log: Snake is dead" << std::endl;
  return _restart;
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_pSnake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  int new_x, new_y;
  _pSnake->GetHead(new_x, new_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    _pSnake->GrowBody();
    _pSnake->IncreaseSpeed(0.02);
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return _pSnake->size; }