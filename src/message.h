#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>

#include "SDL.h"

template <unsigned size>
class MessageBox {
 public:
  virtual int Show() const = 0;
  SDL_MessageBoxData _boxData;
  SDL_MessageBoxColorScheme _colorScheme;
  SDL_MessageBoxButtonData _buttonData[size];
};

class EscapeMessageBox : public MessageBox<2> {
 public:
  EscapeMessageBox();
  int Show() const override;
};

#endif