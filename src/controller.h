#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "game.h"

class Controller {
 public:
  void Start();
  void HandleInput() const;
  void SetSnake(Snake *pSnake) {_pSnake = pSnake;}
  void SetGame(Game *pGame) {_pGame = pGame;}

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  Snake *_pSnake;
  Game *_pGame;
};

#endif