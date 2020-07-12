#include <future>
#include <iostream>

#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  std::unique_ptr<Game> pGame;
  do {
    pGame = std::make_unique<Game>(kGridWidth, kGridHeight,
                                   std::ref(controller), std::ref(renderer));
  } while (pGame->Run(kMsPerFrame));
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "=================================\n";
  std::cout << "Final Score: " << pGame->GetScore() << "\n";
  std::cout << "Final Size: " << pGame->GetSize() << "\n";
  std::cout << "=================================\n";
  return 0;
}