#pragma once

class Action;
class Entity;

namespace ui {

class IUi {
 public:
  virtual bool ActionAvailable() const = 0;
  virtual Action GetAction() const = 0;
  virtual void DisplayDied() const = 0;
  virtual void Display(Entity const& entity) const = 0;
  virtual void Print(char const* message) const = 0;
};

}  // namespace ui
