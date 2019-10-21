#pragma once

#include <api/IUi.h>

class SerialUi : public Ui::IUi {
 public:
  SerialUi(int baudrate) : _available(false) {}

  bool ActionAvailable() const { return _available; }
  Action const &GetAction() const {}
  void DisplayDied() const {}
  void Display(Entity const &entity) const {}

 private:
  uint8_t _available;
};
