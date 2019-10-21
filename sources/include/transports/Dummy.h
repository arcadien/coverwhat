#pragma once

#include <api/ITransport.h>
#include <utility>

namespace transport {
/*!
 * This transport implementation just does nothing, nor send nor receive
 */
class Dummy : public ITransport {
 public:
  ~Dummy() override{};
  void Queue(Action const& action) override {}
  bool ActionAvailable() override { return false; }
  Action const& GetAction() override {
    Action action(Action::HEAL, Entity::Tag::Health,
                  Action::Amount::AMOUNT_FULL, 0);

    return std::move(action);
  }
};
}  // namespace transport

