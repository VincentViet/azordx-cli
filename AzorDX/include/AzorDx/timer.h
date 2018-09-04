#ifndef AZORDX_TIMER_H
#define AZORDX_TIMER_H

namespace azordx {
class Timer {
 public:
  Timer() = delete;
  ~Timer() = delete;

 public:
  static float delta_time;
  static void initialize();
  static void pause();
  static void resume();
};
}  // namespace azordx

#endif  // AZORDX_TIMER_H