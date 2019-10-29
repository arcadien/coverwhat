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

#include <actors/Weapon.h>
#include <api/ITransport.h>
#include <api/Meta.h>
namespace Weapons {

class Vampire : public actors::Weapon {
 public:
  Vampire(transport::ITransport &transport)
      : actors::Weapon(transport, Meta::Actions::DAMAGE5,
                       Meta::Actions::HEAL5) {}
};

}  // namespace Weapons
