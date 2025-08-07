#ifndef INPUT_HPP
#define INPUT_HPP

namespace input {
  enum class Action { None, RotateCW, RotateCCW, Press, LongPress, Btn1, Btn2, Btn3 };
  void init();
  void poll();
  Action getAction();
}

#endif