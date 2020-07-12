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
  Snake *_pSnake; // store the pointer to Snake that it controls
  Game *_pGame;// store the pointer to Game
};

#endif