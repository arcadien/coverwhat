#pragma once

#include <api/Action.h>
#include <regex>

namespace actions {
/*!
 * Transform a string representation into a Action instance
 *
 */
template <typename T,
          typename = std::enable_if<std::is_convertible<T *, Action *>::value>>
class StringActionFactory {
 public:
  static T Create(const std::string &buffer) {
    std::smatch sm;
    if (std::regex_match(buffer, sm, std::regex("(\\w)(\\d*)"))) {
      std::string pType = sm[1];
      std::string pAmount = sm[2];

      IAction::Type type;
      if ("D" == pType) {
        type = IAction::Type::DAMAGE;
      } else if ("H" == pType) {
        type = IAction::Type::HEAL;
      } else {
        type = IAction::Type::NONE;
      }

      IAction::Amount amount;
      if ("1" == pAmount) {
        amount = IAction::Amount::AMOUNT_1;
      } else if ("5" == pAmount) {
        amount = IAction::Amount::AMOUNT_5;
      } else if ("10" == pAmount) {
        amount = IAction::Amount::AMOUNT_10;
      } else if ("25" == pAmount) {
        amount = IAction::Amount::AMOUNT_25;
      } else if ("50" == pAmount) {
        amount = IAction::Amount::AMOUNT_50;
      } else if ("100" == pAmount) {
        amount = IAction::Amount::AMOUNT_100;
      } else if ("250" == pAmount) {
        amount = IAction::Amount::AMOUNT_250;
      } else {
        amount = IAction::Amount::AMOUNT_0;
      }
      return T(type, Entity::Tag::Health, amount, 1);
    } else {
      return T();
    }
  }
};
}  // namespace actions
