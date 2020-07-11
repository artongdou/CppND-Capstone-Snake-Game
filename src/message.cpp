#include "message.h"

#include <iostream>

int EscapeMessageBox::Show() const {
  int button_id;
  if (SDL_ShowMessageBox(&_boxData, &button_id) < 0) {
    SDL_Log("error displaying message box");
    return -1;
  }
  return button_id;
}