#pragma once

#include <actors/Player.h>
#include <actors/Weapon.h>
#include <api/ITransport.h>

#include <utility>

namespace transport {
class Software : public ITransport {
 public:
  Software();

  void Wire(actors::Weapon *weapon, actors::Player *player) {
    _player = player;
  }
  void Queue(Action const &action) override;

  bool ActionAvailable() override { return false; }
  Action const &GetAction() override {
    Action action(Action::HEAL, Entity::Tag::Health,
                  Action::Amount::AMOUNT_FULL, 0);

    return std::move(action);
  }

 private:
  actors::Player *_player;
};
}  // namespace transport
