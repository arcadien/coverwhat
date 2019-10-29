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
#include <string.h>

#if (__clang__)
#include <type_traits>
#endif

namespace actions {
/*!
 * Transform a string representation into a Action instance
 *
 */
#if (__clang__)
template <typename T,
          typename = std::enable_if<std::is_convertible<T *, IAction *>::value>>
class StringActionFactory {
#else
template <typename T>
class StringActionFactory {
#endif
 public:
  static T Create(const char *buffer) {
    int buflen = strlen(buffer);
    if (buflen < 2) {
      return T();
    }
    char *_pAmount = new char[buflen - 1];
    memcpy(_pAmount, &buffer[1], buflen);
    const char *pAmount = _pAmount;

    IAction::Type type;
    if ((char)IAction::Type::DAMAGE == buffer[0]) {
      type = IAction::Type::DAMAGE;
    } else if ((char)IAction::Type::HEAL == buffer[0]) {
      type = IAction::Type::HEAL;
    } else {
      type = IAction::Type::NONE;
    }

    IAction::Amount amount;
    if (strcmp("1", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_1;
    } else if (strcmp("5", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_5;
    } else if (strcmp("10", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_10;
    } else if (strcmp("25", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_25;
    } else if (strcmp("50", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_50;
    } else if (strcmp("100", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_100;
    } else if (strcmp("250", pAmount) == 0) {
      amount = IAction::Amount::AMOUNT_250;
    } else {
      amount = IAction::Amount::AMOUNT_0;
    }
    return T(type, Entity::Tag::Health, amount, 1);
  }
};
}  // namespace actions
