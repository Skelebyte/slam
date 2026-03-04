#include "input.hpp"

using namespace slam;
using namespace slam::input;
using namespace slam::math;

Keybind::Keybind(Keycode code) {
  keycode = code;
  pressed = false;
}

InputAxis::InputAxis(Keycode pos, Keycode neg) {
  this->positive = pos;
  this->negative = neg;
}

int Input::GetAxis(const InputAxis &axis) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (axis.positive < 0 && axis.negative < 0) {
    if (flags & SDL_BUTTON_MASK(-axis.positive) &&
        flags & SDL_BUTTON_MASK(-axis.negative)) {
      return 0;
    }
  }

  if (axis.positive < 0) {
    if (flags == SDL_BUTTON_MASK(-axis.positive)) {
      return 1;
    }
  }

  if (axis.negative < 0) {
    if (flags == SDL_BUTTON_MASK(-axis.negative)) {
      return -1;
    }
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[axis.positive] == true && input[axis.negative] == true) {
    return 0;
  }

  if (input[axis.positive] == true) {
    return 1;
  }

  if (input[axis.negative] == true) {
    return -1;
  }

  return 0;
}

bool Input::GetKey(Keybind *keybind) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (keybind->keycode < 0) { // checking mouse keys
    if (flags == SDL_BUTTON_MASK(-keybind->keycode)) {
      keybind->pressed = true;
      return true;
    } else {
      keybind->pressed = false;
      return false;
    }
    return false;
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[keybind->keycode] == true) {
    keybind->pressed = true;
    return true;
  } else {
    keybind->pressed = false;
    return false;
  }

  return false;
}

bool Input::GetKeyOnce(Keybind *keybind) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (keybind->keycode < 0) { // checking mouse keys
    if (flags & SDL_BUTTON_MASK(-keybind->keycode) &&
        keybind->pressed == false) {
      keybind->pressed = true;
      return true;
    }

    if ((flags & SDL_BUTTON_MASK(-keybind->keycode)) == 0 &&
        keybind->pressed == true) {
      keybind->pressed = false;
      return false;
    }

    return false;
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[keybind->keycode] == true && keybind->pressed == false) {
    keybind->pressed = true;
    return true;
  }

  if (input[keybind->keycode] == false && keybind->pressed == true) {
    keybind->pressed = false;
    return false;
  }

  return false;
}

Vec2 Input::GetRawMousePosition() {
  Vec2 pos;
  SDL_GetMouseState(&pos.x, &pos.y);
  return pos;
}

math::Vec2 Input::GetMousePosition() {
  Vec2 pos;
  SDL_GetRelativeMouseState(&pos.x, &pos.y);

  return pos;
}

void Input::SetCursor(bool locked, bool hidden) {
  if (locked) {
    SDL_SetWindowRelativeMouseMode(Engine::Get().window->GetSDLWindow(), true);
    SDL_WarpMouseInWindow(Engine::Get().window->GetSDLWindow(),
                          (float)Engine::Get().window->GetDimensions().x / 2,
                          (float)Engine::Get().window->GetDimensions().y / 2);
  } else {
    SDL_SetWindowRelativeMouseMode(Engine::Get().window->GetSDLWindow(), false);
  }

  if (hidden) {
    SDL_HideCursor();
  } else {
    SDL_ShowCursor();
  }
  // SDL_ShowCursor();
}