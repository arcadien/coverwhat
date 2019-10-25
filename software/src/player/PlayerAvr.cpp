//------------------------------------------------------------------------------
// Include the IRremote library header
//
#include <Arduino.h>
#include <IRremote.h>

#include <tools/RGBColor.h>

//------------------------------------------------------------------------------
// Tell IRremote which Arduino pin is connected to the IR Receiver (TSOP4838)
//
int recvPin = 2;
IRrecv irrecv(recvPin);
IRsend irsend;

//+=============================================================================
// Configure the Arduino
//

int health;
int livesCounter;
int ammo;
RGBColor rgbColor;

char* heroes[] = {"dps", "tank", "healer", "sniper"};
uint8_t heroIndex;

int hue;
int saturation;

int ledPinR = 5;
int ledPinG = 6;
int ledPinB = 9;

void panel() {
  Serial.println("*.kwl");
  Serial.println("clear_panel()");
  Serial.print("set_grid_size(10,5)");
  Serial.println("");
  Serial.print("add_text(0,0,large,L");
  Serial.print(",Health,245,240,245,");
  Serial.println(")");
  Serial.print("add_text(0,4,large,L");
  Serial.print(",Hero,245,240,245,)");
  Serial.println("");
  Serial.print("add_text(0,1,large,L");
  Serial.print(",Ammo,245,240,245,)");
  Serial.println("");
  Serial.print("add_text(0,3,large,L");
  Serial.print(",Spawns,245,240,245,");
  Serial.println(")");
  Serial.print("add_text_box(2,3,1,L");
  Serial.print(",\"\\n \",245,240,245,S");
  Serial.println(")");
  Serial.print("add_text_box(2,4,4,L");
  Serial.println(",,245,240,245,E)");
  Serial.print("add_button(6,4,9,C,c");
  Serial.println(")");
  Serial.print("add_button(8,3,29,R,");
  Serial.println("r)");
  Serial.print("add_gauge(2,0,4,0,50");
  Serial.println("0,0,L,,l,5,0)");
  Serial.print("add_gauge(2,1,5,0,10");
  Serial.println("0,100,A,,,10,10)");
  Serial.print("add_buzzer(9,0,1,D,a");
  Serial.println(",true,100.00)");
  Serial.print("add_buzzer(9,1,1,H,b");
  Serial.println(",false,100.00)");
  Serial.print("add_buzzer(9,2,1,M,c");
  Serial.println(",false,100.00)");
  Serial.print("set_panel_notes(,,,)");
  Serial.println("");
  Serial.println("run()");
  Serial.println("*");
}

void postColors(RGBColor const& rgb_color) {
  // 0 is max value for RGB leds
  // clamp between 0 and maxBrightness to save battery
  const uint8_t maxBrightness = 100;
  analogWrite(ledPinR, 255 - map(rgb_color.red, 0, 255, 0, maxBrightness));
  analogWrite(ledPinG, 255 - map(rgb_color.green, 0, 255, 0, maxBrightness));
  analogWrite(ledPinB, 255 - map(rgb_color.blue, 0, 255, 0, maxBrightness));
}

void setup() {
  Serial.begin(57600);

  panel();
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

