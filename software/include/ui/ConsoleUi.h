/*
 * This file is part of the KOTH distribution (https://github.com/arcadien/koth)
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

#include <actions/StringActionFactory.h>
#include <api/IUi.h>
#include <tools/Timer.h>
#include <iostream>
#include <string>

#include <mutex>
#include <thread>

namespace ui {
/*!
 * Implementation for interaction with system stream `cout` and `cin`
 *
 */
class ConsoleUi : public IUi {
 public:
  static const uint8_t READ_DELAY_MS;

  ConsoleUi(std::istream &inputStream)
      : _available(false), _inputStream(inputStream) {
    _inputReader.SetInterval(
        [this]() {
          std::string buffer;
          std::getline(_inputStream, buffer);
          std::cout << "[debug] Read " << buffer << std::endl;
          if (buffer.compare("Q") == 0) {
            exit(0);
          } else {
            _actionQueue[0] =
                actions::StringActionFactory<Action>::Create(buffer.c_str());
            _available = true;
          }
        },
        READ_DELAY_MS);
  }

  ~ConsoleUi() { _inputReader.Stop(); }

  bool ActionAvailable() const override { return _available; }

  Action GetAction() const override {
    _available = false;
    return _actionQueue[0];
  }
  void DisplayDied() const override {}
  void Display(Entity const &entity) const override {
    std::cout << entity.GetValue() << std::endl;
  }

  void Print(char const *message) const override {
    std::cout << message << std::endl;
  }

 private:
  std::istream &_inputStream;
  tools::Timer _inputReader;
  mutable bool _available;
  Action _actionQueue[1];
};
}  // namespace ui
