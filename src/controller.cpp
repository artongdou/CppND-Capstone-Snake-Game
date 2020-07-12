#include "controller.h"

#include <future>
#include <iostream>

#include "SDL.h"
#include "message.h"
#include "snake.h"

void Controller::HandleInput() const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      _pGame->EndGame();
      std::cout << "log: Window closed" << std::endl;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          _pSnake->ChangeDirection(Snake::Direction::kUp);
          break;

        case SDLK_DOWN:
          _pSnake->ChangeDirection(Snake::Direction::kDown);
          break;

        case SDLK_LEFT:
          _pSnake->ChangeDirection(Snake::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          _pSnake->ChangeDirection(Snake::Direction::kRight);
          break;
        case SDLK_ESCAPE:
          EscapeMessageBox msgBox;
          int button_id = msgBox.Show();
          if (button_id == -1) {
            SDL_Log("no selection");
          } else if (button_id == 0) {
            std::cout << "log: End button hit" << std::endl;
            _pGame->EndGame();
          } else {
            std::cout << "log: Restart button hit" << std::endl;
            _pGame->RestartGame();
          }
          break;
      }
    }
  }
}