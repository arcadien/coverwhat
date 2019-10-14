#pragma once

class Action;

namespace transport {

/*!
 * Defines the interface needed to transmit and receive \ref Action
 *
 *
 *
 */
class ITransport {
public:
  virtual ~ITransport() = default;

  virtual void Queue(Action const &action) = 0;
};

} // namespace transport
