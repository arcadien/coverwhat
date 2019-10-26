#pragma once

#include <api/IUi.h>

namespace ui {
class SerialUi : public IUi {
 public:
  SerialUi(int baudrate) : _available(false) {}

  bool ActionAvailable() const override { return _available; }
  Action const &GetAction() const override { return Action(); }
  void DisplayDied() const override {}
  void Display(Entity const &entity) const override {}
  void Print(char const *message) const override;

 private:
  uint8_t _available;
};
}  // namespace ui
