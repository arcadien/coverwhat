#pragma once

class Action;

namespace transport {
class ITransport {
public:
  virtual ~ITransport() = default;

  virtual void Queue(Action const &action) = 0;
};

} // namespace transport
