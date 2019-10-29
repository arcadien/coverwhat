/*
 * This file is part of the KOTH distribution (https://github.com/arcadien/koth)
 *
 * Copyright (c) 2019 Aurélien Labrosse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <api/Action.h>
#include <api/ITransport.h>

namespace actors {
class Weapon {
 public:
  Weapon(transport::ITransport &transport, Action const &primaryAction,
         Action const &secondaryAction)
      : _transport(transport),
        _primary(primaryAction),
        _secondary(secondaryAction) {}

  Action const &GetPrimary() { return _primary; }
  Action const &GetSecondary() { return _secondary; }

  void TriggerPrimaryAction() { _transport.Queue(GetPrimary()); }
  void TriggerSecondaryAction() { _transport.Queue(GetSecondary()); }

 private:
  transport::ITransport &_transport;
  Action const &_primary;
  Action const &_secondary;
};
}  // namespace actors
