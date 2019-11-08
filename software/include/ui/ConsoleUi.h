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

#include <actions/StringActionFactory.h>
#include <api/IUi.h>
#include <tools/Timer.h>

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace ui {
/*!
 * Implementation for interaction with system stream `cout` and `cin`
 *
 */
class ConsoleUi : public IUi {
public:
  static const uint8_t READ_DELAY_MS;

  ConsoleUi(std::istream &inputStream, std::ostream &outputStream)
      : _available(false), _inputStream(inputStream),
        _outputStream(outputStream) {
    _inputReader.SetInterval(
        [this]() {
          std::string buffer;
          std::getline(_inputStream, buffer);
          _outputStream << "[debug] Read " << buffer << std::endl;
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
    _outputStream << "{'tag': " << static_cast<uint16_t>(entity.GetTag())
                  << ", 'value': " << entity.GetValue() << "}" << std::endl;
  }

  void Print(char const *message) const override {
    _outputStream << message << std::endl;
  }

private:
  std::istream &_inputStream;
  std::ostream &_outputStream;
  tools::Timer _inputReader;
  mutable bool _available;
  Action _actionQueue[1];
};
} // namespace ui
