#ifndef SLAM_INPUT_HPP
#define SLAM_INPUT_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../engine.hpp"
#include "../math/mathf.hpp"

namespace slam::input {

enum Keycode {
  LMB = -1,
  MMB = -2,
  RMB = -3,
  XMB1 = -4,
  XMB2 = -5,
  KEY = 0,
  A = 4,
  B = 5,
  C = 6,
  D = 7,
  E = 8,
  F = 9,
  G = 10,
  H = 11,
  I = 12,
  J = 13,
  K = 14,
  L = 15,
  M = 16,
  N = 17,
  O = 18,
  P = 19,
  Q = 20,
  R = 21,
  S = 22,
  T = 23,
  U = 24,
  V = 25,
  W = 26,
  X = 27,
  Y = 28,
  Z = 29,
  NUM_1 = 30,
  NUM_2 = 31,
  NUM_3 = 32,
  NUM_4 = 33,
  NUM_5 = 34,
  NUM_6 = 35,
  NUM_7 = 36,
  NUM_8 = 37,
  NUM_9 = 38,
  NUM_0 = 39,
  RETURN = 40,
  ESC = 41,
  BACKSPACE = 42,
  TAB = 43,
  SPACE = 44,
  TILDE_GRAVE = 53,
  F1 = 58,
  F2 = 59,
  F3 = 60,
  F4 = 61,
  F5 = 62,
  F6 = 63,
  F7 = 64,
  F8 = 65,
  F9 = 66,
  F10 = 67,
  F11 = 68,
  F12 = 69,
  R_ARROW = 79,
  L_ARROW = 80,
  D_ARROW = 81,
  U_ARROW = 82,
  L_CTRL = 224,
  L_SHIFT = 225,
  L_ALT = 226,
  R_CTRL = 228,
  R_SHIFT = 229,
  R_ALT = 230

};

struct Keybind {
  Keybind(Keycode code);
  Keycode keycode;
  bool pressed;
};

struct InputAxis {
  InputAxis(Keycode pos, Keycode neg);
  Keycode positive;
  Keycode negative;
};

struct Input : public Singleton<Input> {
  static i32 GetAxis(const InputAxis &axis);
  static bool GetKey(Keybind *keybind);
  static bool GetKeyOnce(Keybind *keybind);
  static math::Vec2 GetRawMousePosition();
  static math::Vec2 GetMousePosition();
  static void SetCursor(bool locked, bool hidden);

private:
  bool mouseHidden;
  bool mouseLocked;
};
} // namespace slam::input

#endif