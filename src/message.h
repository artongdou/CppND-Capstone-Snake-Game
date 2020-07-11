#ifndef message_h
#define message_h

#include <memory>

#include "SDL.h"

class MessageBox {
 public:
  virtual int Show() const = 0;
};

class EscapeMessageBox : public MessageBox {
 public:
    int Show() const override;
 private:
  const SDL_MessageBoxData _boxData = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Quit/Restart",             /* .title */
      "select a button",          /* .message */
      SDL_arraysize(_buttonData), /* .numbuttons */
      _buttonData,                /* .buttons */
      &_colorScheme               /* .colorScheme */
  };
  const SDL_MessageBoxColorScheme _colorScheme = {
      {/* .colors (.r, .g, .b) */
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
  const SDL_MessageBoxButtonData _buttonData[2] = {
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "End"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Restart"},
  };
};

#endif