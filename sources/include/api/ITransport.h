#pragma once

class Action;

namespace transport {

/*!
 * Defines interface needed to transmit and receive \ref Action
 *
 *
 *
 */
class ITransport {
 public:
  virtual ~ITransport() = default;

  /*!
   * Push an Action to send in the ITransport implementation queue
   */
  virtual void Queue(Action const& action) = 0;

  virtual bool ActionAvailable() = 0;

  virtual const Action GetAction() = 0;
};

}  // namespace transport
