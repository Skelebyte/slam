#include "input.hpp"

using namespace slam;
using namespace slam::input;
using namespace slam::math;

Keybind::Keybind(Keycode code) {
  keycode = code;
  pressed = false;
}

InputAxis::InputAxis(CRef<Keycode> neg, CRef<Keycode> pos) {
  this->positive = pos;
  this->negative = neg;
}

f32 Input::GetAxis(CRef<InputAxis> axis) {
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

f32 Input::GetAxis(const Keycode &neg, const Keycode &pos) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (pos < 0 && neg < 0) {
    if (flags & SDL_BUTTON_MASK(-pos) && flags & SDL_BUTTON_MASK(-neg)) {
      return 0;
    }
  }

  if (pos < 0) {
    if (flags == SDL_BUTTON_MASK(-pos)) {
      return 1;
    }
  }

  if (neg < 0) {
    if (flags == SDL_BUTTON_MASK(-neg)) {
      return -1;
    }
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[pos] == true && input[neg] == true) {
    return 0;
  }

  if (input[pos] == true) {
    return 1;
  }

  if (input[neg] == true) {
    return -1;
  }

  return 0;
}

bool Input::GetKey(Ptr<Keybind> keybind) {
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

bool Input::GetKey(const Keycode &keycode) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (keycode < 0) { // checking mouse keys
    if (flags == SDL_BUTTON_MASK(-keycode)) {

      return true;
    } else {

      return false;
    }
    return false;
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[keycode] == true) {

    return true;
  } else {

    return false;
  }

  return false;
}

bool Input::GetKeyOnce(Ptr<Keybind> keybind) {
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

bool Input::GetKeyOnce(const Keycode &keycode) {
  SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

  if (keycode < 0) { // checking mouse keys
    if (flags & SDL_BUTTON_MASK(-keycode) && CheckLastInput(keycode) == false) {
      AddLastInput(keycode);
      return true;
    }

    if ((flags & SDL_BUTTON_MASK(-keycode)) == 0 &&
        CheckLastInput(keycode) == true) {
      RemoveLastInput(keycode);
      return false;
    }

    return false;
  }

  const bool *input = SDL_GetKeyboardState(NULL);
  if (input[keycode] == true && CheckLastInput(keycode) == false) {
    AddLastInput(keycode);
    return true;
  }

  if (input[keycode] == false && CheckLastInput(keycode) == true) {
    RemoveLastInput(keycode);
    return false;
  }

  return false;
}

Vec2 Input::GetRawMousePosition() {
  Vec2 pos;
  SDL_GetMouseState(&pos.x, &pos.y);
  return pos;
}

Vec2 Input::GetMousePosition() {
  if (Get().getMousePosCalled) {
    return Get().mousePosCache;
  }

  Vec2 pos;
  SDL_GetRelativeMouseState(&pos.x, &pos.y);

  Get().mousePosCache = pos;
  Get().getMousePosCalled = true;

  return pos;
}

void Input::SetCursor(bool locked, bool hidden) {
  if (locked) {
    SDL_SetWindowRelativeMouseMode(Engine::GetWindow()->GetSDLWindow(), true);
    SDL_WarpMouseInWindow(Engine::GetWindow()->GetSDLWindow(),
                          (f32)Engine::GetWindow()->GetDimensions().x / 2,
                          (f32)Engine::GetWindow()->GetDimensions().y / 2);
  } else {
    SDL_SetWindowRelativeMouseMode(Engine::GetWindow()->GetSDLWindow(), false);
  }

  if (hidden) {
    SDL_HideCursor();
  } else {
    SDL_ShowCursor();
  }
  // SDL_ShowCursor();
}

void Input::INTERNALResetMousePositionCache() {
  if (!Get().getMousePosCalled)
    return;

  Get().getMousePosCalled = false;
  Get().mousePosCache = Vec2(0);
}

bool Input::CheckLastInput(const Keycode &target) {
  for (u32 i = 0; i < Get().inputFromLastFrame.Size(); i++) {
    if (Get().inputFromLastFrame[i] == (i32)target) {
      return true;
    }
  }

  return false;
}

void Input::AddLastInput(const Keycode &target) {
  if (CheckLastInput(target))
    return;

  Get().inputFromLastFrame.Add(target);
}

void Input::RemoveLastInput(const Keycode &target) {
  if (!CheckLastInput(target))
    return;

  Get().inputFromLastFrame.RemoveElement((i32)target);
}