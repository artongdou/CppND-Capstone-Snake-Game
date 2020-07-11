#include "snake.h"

#include <cmath>
#include <iostream>

std::future<void> Snake::Start(std::size_t target_frame_duration) {
  auto fut = std::async(std::launch::async, &Snake::Update, this,
                        target_frame_duration);
  return fut;
}

void Snake::Update(std::size_t target_frame_duration) {
  Uint32 last_update = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  while (IsAlive()) {
    frame_start = SDL_GetTicks();
    // std::cout << "Snake Update..." << std::endl;
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(
            head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};  // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a
    // new cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
      UpdateBody(current_cell, prev_cell);
    }

    frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Snake::UpdateHead() {
  std::unique_lock lock{_mtx};
  switch (_direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  std::unique_lock lock{_mtx};
  // Add previous head location to vector
  _body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    _body.erase(_body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : _body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      _alive = false;
    }
  }
}

void Snake::ChangeDirection(Direction new_dir) {
  std::unique_lock lock{_mtx};
  if (_oppositeDir[new_dir] != _direction) {
    _direction = new_dir;
  }
}

void Snake::GrowBody() {
  std::unique_lock lock{_mtx};
  growing = true;
}

void Snake::IncreaseSpeed(float deltaSpd) {
  std::unique_lock lock{_mtx};
  speed += deltaSpd;
}

bool Snake::IsAlive() const {
  std::shared_lock lock{_mtx};
  return _alive;
};

void Snake::GetHead(int &x, int &y) const {
  std::shared_lock lock{_mtx};
  x = static_cast<int>(head_x);
  y = static_cast<int>(head_y);
}

std::vector<SDL_Point> Snake::GetBody() const {
  std::shared_lock lock{_mtx};
  return std::vector<SDL_Point>{_body};
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  std::shared_lock lock{_mtx};
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : _body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}