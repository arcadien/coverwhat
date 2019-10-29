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

