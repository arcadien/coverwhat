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

#include <IRremote.h>
#include <IRremoteInt.h>
#include <api/ITransport.h>
#include <api/IUi.h>

namespace transports {
class InfraredRc5 : public ITransport {
 public:
  infraredRc5(Mode mode, ui::IUi const& ui) : _ui(ui) {}

  void Queue(Action const& action) { send(action.ToLong()); }

  bool ActionAvailable() {
    bool result = false;
    if (irrecv.decode(&_irMessage)) {
      ui.Trace("IR_RECV");

      unsigned long value = _irMessage.value;
      unsigned long mask = 0b100000000000;
      value &= ~mask;
      _action = Action(value);
      result = true;
    }
    return result;
  }

  const Action GetAction() override { return _action; }

  enum Mode {
    EMITTER,
    RECEIVER,
    BOTH,
  };

 private:
  void send(uint16_t code) {
    unsigned long time;
    digitalWrite(LED, HIGH);
    time = millis();
    irsend.sendRC5(code, IR_MESSAGE_LENGTH);
    unsigned long duration = millis() - time;
    Serial.print("message duration: ");
    Serial.print(duration);
    Serial.println("ms");
    digitalWrite(LED, LOW);
  }
  ui : IUi const& _ui;
  IRsend irsend;
  decode_results _irMessage;
};
}  // namespace transports

