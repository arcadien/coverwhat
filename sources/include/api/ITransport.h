#pragma once

namespace Actor {
class Player;
class Weapon;
} // namespace Actor
class Action;

namespace transport {
class ITransport {
public:
  virtual ~ITransport() = default;

  virtual void Queue(Action const &action) = 0;
};

/*!
 * This transport implementation just does nothing, nor send nor receive
 */
class Dummy : public ITransport {
public:
  ~Dummy() override = default;
  void Queue(Action const &action) override {
  }
};

class Software : public ITransport {
public:
  ~Software() override = default;

  Software() = default;

  void Wire(Actor::Weapon *weapon, Actor::Player *player) {
    _player = player;
  }
  void Queue(Action const &action) override;

private:
  Actor::Player *_player;
};
} // namespace transport
