#pragma once

#include <api/Action.h>
#include <api/ITransport.h>

namespace actors {
class Weapon {
public:
  Weapon(transport::ITransport &transport, Action const &primaryAction,
         Action const &secondaryAction)
      : _transport(transport), _primary(primaryAction),
        _secondary(secondaryAction) {
  }

  Action const &GetPrimary() {
    return _primary;
  }
  Action const &GetSecondary() {
    return _secondary;
  }

  void TriggerPrimaryAction() {
    _transport.Queue(GetPrimary());
  }
  void TriggerSecondaryAction() {
    _transport.Queue(GetSecondary());
  }

private:
  transport::ITransport &_transport;
  Action const &_primary;
  Action const &_secondary;
};
} // namespace actors
