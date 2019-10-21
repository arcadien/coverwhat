#pragma once

#include <api/IUi.h>
#include <tools/Timer.h>

#include <iostream>
#include <regex>
#include <string>

#include <mutex>
#include <thread>

/*!
 * Implementation for interaction with system stream `cout` and `cin`
 *
 */
class ConsoleUi : public Ui::IUi {
 public:
  ConsoleUi() : _available(false) {
    _inputReader.SetInterval(
        [this]() {
          std::string buffer;
          std::getline(std::cin, buffer);
          std::cout << "[debug] Read " << buffer << std::endl;
          if (buffer.compare("Q") == 0) {
            exit(0);
          } else {
            _actionQueue[0] = ActionFactory::Create(buffer);
            _available = true;
          }
        },
        1000);
  }

  ~ConsoleUi() { _inputReader.Stop(); }

  bool ActionAvailable() const override { return _available; }

  Action GetAction() const override {
    _available = false;
    return _actionQueue[0];
  }
  void DisplayDied() const override {}
  void Display(Entity const &entity) const override {
    std::cout << entity.GetValue() << std::endl;
  }

  void Print(std::string const &message) const override {
    std::cout << message << std::endl;
  }

 private:
  /*!
   * Transform a string representation into a Action instance
   *
   * This construction is largely dependent of the used UI, so
   * it is implemented here rather than directly in Action class
   */
  class ActionFactory {
   public:
    static Action Create(const std::string &buffer) {
      std::smatch sm;
      if (std::regex_match(buffer, sm, std::regex("(\\w)(\\d*)"))) {
        std::string pType = sm[1];
        std::string pAmount = sm[2];

        Action::Type type;
        if ("D" == pType) {
          type = Action::Type::DAMAGE;
        } else if ("H" == pType) {
          type = Action::Type::HEAL;
        } else {
          type = Action::Type::NONE;
        }

        Action::Amount amount;
        if ("5" == pAmount) {
          amount = Action::Amount::AMOUNT_5;
        } else if ("10" == pAmount) {
          amount = Action::Amount::AMOUNT_10;
        } else if ("25" == pAmount) {
          amount = Action::Amount::AMOUNT_25;
        } else if ("50" == pAmount) {
          amount = Action::Amount::AMOUNT_50;
        } else if ("100" == pAmount) {
          amount = Action::Amount::AMOUNT_100;
        } else if ("250" == pAmount) {
          amount = Action::Amount::AMOUNT_250;
        } else if ("FULL" == pAmount) {
          amount = Action::Amount::AMOUNT_FULL;
        } else {
          amount = Action::Amount::AMOUNT_0;
        }
        return Action(type, Entity::Tag::Health, amount, 1);
      } else {
        return Action();
      }
    }
  };
  tools::Timer _inputReader;
  mutable bool _available;
  Action _actionQueue[1];
};
