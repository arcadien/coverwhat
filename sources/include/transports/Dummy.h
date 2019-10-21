#pragma once

#include <api/ITransport.h>

namespace transport {
/*!
 * This transport implementation just does nothing, nor send nor receive
 */
class Dummy : public ITransport {
 public:
  ~Dummy() override{};
  void Queue(Action const& action) override {}
  bool ActionAvailable() override { return false; }
  Action const GetAction() override { return Action(); }
};
}  // namespace transport

