#pragma once

#include <string>

class Action;
class Entity;

namespace Ui {

class IUi {
 public:
  virtual bool ActionAvailable() const = 0;
  virtual Action GetAction() const = 0;
  virtual void DisplayDied() const = 0;
  virtual void Display(Entity const& entity) const = 0;
  virtual void Print(std::string const& message) const = 0;
};

}  // namespace Ui
