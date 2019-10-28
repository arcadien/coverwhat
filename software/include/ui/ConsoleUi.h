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
                actions::StringActionFactory<Action>::Create(buffer);
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
