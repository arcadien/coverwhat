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

//------------------------------------------------------------------------------
// Include the IRremote library header
//
#include <Arduino.h>
#include <IRremote.h>

#include <tools/RGBColor.h>
#include <ui/BluetoothElectronicUi.h>

//------------------------------------------------------------------------------
// Tell IRremote which Arduino pin is connected to the IR Receiver (TSOP4838)
//
int recvPin = 2;
IRrecv irrecv(recvPin);
IRsend irsend;

//+=============================================================================
// Configure the Arduino
//

ui::BluetoothElectronicUi userInterface(57600);

int health;
int livesCounter;
int ammo;
RGBColor rgbColor;

const char* heroes[] = {"dps", "tank", "healer", "sniper"};
uint8_t heroIndex;

int hue;
int saturation;

int ledPinR = 5;
int ledPinG = 6;
int ledPinB = 9;

void postColors(RGBColor const& rgb_color) {
  // 0 is max value for RGB leds
  // clamp between 0 and maxBrightness to save battery
  const uint8_t maxBrightness = 100;
  analogWrite(ledPinR, 255 - map(rgb_color.red, 0, 255, 0, maxBrightness));
  analogWrite(ledPinG, 255 - map(rgb_color.green, 0, 255, 0, maxBrightness));
  analogWrite(ledPinB, 255 - map(rgb_color.blue, 0, 255, 0, maxBrightness));
}

void setup() {
  heroIndex = 0;
  livesCounter = 1;
  health = 500;
  ammo = 100;

  Serial.println("*L" + String(health) + "*");
  Serial.println("*S" + String(livesCounter) + "*");
  Serial.println("*E" + String(heroes[heroIndex]) + "*");
  Serial.println("*A" + String(ammo) + "*");

  irrecv.enableIRIn();  // Start the receiver

  pinMode(5, OUTPUT);  // red
  pinMode(6, OUTPUT);  // green
  pinMode(9, OUTPUT);  // blue

  int saturation = 255;  // saturation is a number between 0 - 255
  int brightness = 255;  // value is a number between 0 - 255

  rgbColor.FromHSV(145, saturation, brightness);
  postColors(rgbColor);
}

//+=============================================================================
// The repeating section of the code
//
void loop() {
  if (Serial.available() > 0) {
    uint8_t incomingByte = Serial.read();

    Serial.println("Received: " + incomingByte);

    if (incomingByte == 'R') {
      health = 500;
      livesCounter++;

      for (int i = 0; i < 500; i++) {
        hue = map(i, 0, 500, 0,
                  145);  // map health between red (dead) and green-blue
        rgbColor.FromHSV(hue, 255, 255);
        postColors(rgbColor);
        delay(5);  // 5*500 = 2.5s
      }

      health = 500;
      Serial.println("*L" + String(health) + "*");
      Serial.println("*S" + String(livesCounter) + "*");

    }

    else if (incomingByte == 'C') {
      // change hero type
      // simulate using a marvelous colour shade
      RGBColor tempColor;
      int saturation = 255;  // saturation is a number between 0 - 255
      int brightness = 255;  // value is a number between 0 - 255

      for (int i = health; i > 0; i--) {
        hue = map(i, 0, 500, 0,
                  145);  // map health between red (dead) and green-blue
        tempColor.FromHSV(hue, saturation, brightness);
        postColors(tempColor);
        delay(5);
      }

      for (int i = 0; i < health; i++) {
        hue = map(i, 0, 500, 0,
                  145);  // map health between red (dead) and green-blue
        tempColor.FromHSV(hue, saturation, brightness);
        postColors(tempColor);
        delay(5);
      }

      if (heroIndex < 3) {
        heroIndex++;

      } else {
        heroIndex = 0;
      }
      Serial.println("*E" + String(heroes[heroIndex]) + "*");
    }
  }

  decode_results results;  // Somewhere to store the results

  if (irrecv.decode(&results)) {  // Grab an IR code

    // All protocols have data
    Serial.print("Raw IR value = 0b");
    Serial.print(results.value, BIN);

    unsigned long value = results.value;
    unsigned long mask = 0b100000000000;
    value &= ~mask;

    // Serial.print("Value = 0b");
    // Serial.print(value, BIN);
    // Serial.println(";");

    if (health > 0) {
      if (value > 0 && value < 4) {
        Serial.println("*DV10*");
      }

      if (value == 1) {
        // Serial.println("received simple shot");
        health = max(0, health - 15);
      }
      if (value == 2) {
        // Serial.println("received hard shot");
        health = max(0, health - 30);
      }
      if (value == 3) {
        // Serial.println("received head shot");
        health = 0;
      }
      if (value == 4) {
        if (health < 500) {
          Serial.println("*HV10*");
        }
        health = min(500, health + 20);
      }
      if (health == 0) {
        // just died
        Serial.println("*MV10*");
      }
    }

    Serial.println("*L" + String(health) + "*");

    if (health > 0) {
      hue = map(health, 0, 500, 0, 145);  // hue is a number between 0 and 360
      int saturation = 255;  // saturation is a number between 0 - 255
      int brightness = 255;  // value is a number between 0 - 255

      rgbColor.FromHSV(hue, saturation, brightness);  // converts HSB to RGB
    } else {
      rgbColor.red = 0;
      rgbColor.green = 0;
      rgbColor.blue = 0;
    }

    postColors(rgbColor);

    irrecv.resume();  // Prepare for the next value
  }
}

