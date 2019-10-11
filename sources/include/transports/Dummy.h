#pragma once

#include <api/ITransport.h>

namespace transport {
/*!
 * This transport implementation just does nothing, nor send nor receive
 */
class Dummy : public ITransport {
public:
  ~Dummy() override{};
  void Queue(Action const &action) override {
  }
};
} // namespace transport

