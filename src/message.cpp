#include "message.h"

#include <iostream>

EscapeMessageBox::EscapeMessageBox() {
  _boxData = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Quit/Restart",             /* .title */
      "select a button",          /* .message */
      SDL_arraysize(_buttonData), /* .numbuttons */
      _buttonData,                /* .buttons */
      &_colorScheme               /* .colorScheme */
  };
  _colorScheme = {{/* .colors (.r, .g, .b) */
                   /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                   {255, 0, 0},
                   /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                   {0, 255, 0},
                   /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                   {255, 255, 0},
                   /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                   {0, 0, 255},
                   /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                   {255, 0, 255}}};
  _buttonData[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "End"};
  _buttonData[1] = {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Restart"};
}

int EscapeMessageBox::Show() const {
  int button_id;
  if (SDL_ShowMessageBox(&_boxData, &button_id) < 0) {
    SDL_Log("error displaying message box");
    return -1;
  }
  return button_id;
}