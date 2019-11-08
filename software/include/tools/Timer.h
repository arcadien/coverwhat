/*
 * This file is part of the Hack distribution (https://github.com/arcadien/Hack)
 *
 * Copyright (c) 2019 Aurélien Labrosse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
  template <typename Function> void SetTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
      if (this->clear)
        return;
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      if (this->clear)
        return;
      function();
    });
    t.detach();
  }

  template <typename Function>
  void SetInterval(Function function, int interval) {
    this->clear = false;
    std::thread t([=]() {
      while (true) {
        if (this->clear)
          return;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        if (this->clear)
          return;
        function();
      }
    });
    t.detach();
  }
  void Stop() { this->clear = true; }
};
} // namespace tools
