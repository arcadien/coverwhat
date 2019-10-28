#pragma once

#include <api/Action.h>
#include <string.h>

namespace actions {
/*!
 * Transform a string representation into a Action instance
 *
 */
#if (__clang__)
#include <type_traits>
template <typename T,
          typename = std::enable_if<std::is_convertible<T *, Action *>::value>>
#else
template <typename T>
#endif
class StringActionFactory {
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
