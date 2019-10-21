#pragma once

#include <mutex>
#include <thread>

namespace tools {
/*!
 * Run a function in a separate thread
 *
 * The class has a `Stop()` method which allow to terminate child thread.
 */
class Timer {
  bool clear = false;

 public:
  template <typename Function>
  void SetTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
      if (this->clear) return;
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      if (this->clear) return;
      function();
    });
    t.detach();
  }

  template <typename Function>
  void SetInterval(Function function, int interval) {
    this->clear = false;
    std::thread t([=]() {
      while (true) {
        if (this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        if (this->clear) return;
        function();
      }
    });
    t.detach();
  }
  void Stop() { this->clear = true; }
};
}  // namespace tools
