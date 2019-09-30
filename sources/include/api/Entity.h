#pragma once

#include <stdint.h>

class Entity {
public:
  enum class Tag : uint16_t { Health = 0x0 };

  Entity(Tag const &tag, uint16_t initialValue)
      : _tag(tag), _initialValue(initialValue), _currentValue(initialValue) {}

  uint16_t GetValue() { return _currentValue; }
  void SetValue(uint16_t value) {

    if (value > _initialValue) {
      _currentValue = _initialValue;
    } else {
      _currentValue = value;
    }
  }

private:
  Tag _tag;
  uint16_t _initialValue;
  uint16_t _currentValue;
};
