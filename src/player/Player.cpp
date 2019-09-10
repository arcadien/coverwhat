//------------------------------------------------------------------------------
// Include the IRremote library header
//
#include <Arduino.h>
#include <IRremote.h>

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
// getRGB function stores RGB values in this array
// use these values for the red, blue, green led.
int rgb_colors[3];

char *heroes[] = { "dps", "tank",  "healer", "sniper"};
uint8_t heroIndex;

int hue;
int saturation;


int ledPinR = 5;
int ledPinG = 6;
int ledPinB = 9;

void panel()
{
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

const byte dim_curve[] = {
  0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
  4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
  6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
  8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
  15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
  20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
  27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
  36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
  48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
  83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
  110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
  146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
  193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};
void postColors(int* rgb_colors) {
  
  // 0 is max value for RGB leds
  // clamp between 0 and maxBrightness to save battery
  const uint8_t maxBrightness = 100;
  analogWrite(ledPinR, 255 - map(rgb_colors[0], 0, 255, 0, maxBrightness)); // red value in index 0 of rgb_colors array
  analogWrite(ledPinG, 255 - map(rgb_colors[1], 0, 255, 0, maxBrightness)); // green value in index 1 of rgb_colors array
  analogWrite(ledPinB, 255 - map(rgb_colors[2], 0, 255, 0, maxBrightness)); // blue value in index 2 of rgb_colors array
}



void getRGB(int hue, int sat, int val, int colors[3]) {
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.
  */

  val = dim_curve[val];
  sat = 255 - dim_curve[255 - sat];

  int r;
  int g;
  int b;
  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0] = val;
    colors[1] = val;
    colors[2] = val;
  } else  {

    base = ((255 - sat) * val) >> 8;

    switch (hue / 60) {
      case 0:
        r = val;
        g = (((val - base) * hue) / 60) + base;
        b = base;
        break;

      case 1:
        r = (((val - base) * (60 - (hue % 60))) / 60) + base;
        g = val;
        b = base;
        break;

      case 2:
        r = base;
        g = val;
        b = (((val - base) * (hue % 60)) / 60) + base;
        break;

      case 3:
        r = base;
        g = (((val - base) * (60 - (hue % 60))) / 60) + base;
        b = val;
        break;

      case 4:
        r = (((val - base) * (hue % 60)) / 60) + base;
        g = base;
        b = val;
        break;

      case 5:
        r = val;
        g = base;
        b = (((val - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }

    colors[0] = r;
    colors[1] = g;
    colors[2] = b;
  }
}
void  setup ( )
{
  Serial.begin(115200);   // Status message will be sent to PC at 9600 baud

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

  pinMode(5, OUTPUT); // red
  pinMode(6, OUTPUT); // green
  pinMode(9, OUTPUT); // blue

  int saturation = 255;                               // saturation is a number between 0 - 255
  int brightness = 255;                           // value is a number between 0 - 255

  getRGB(145, saturation, brightness, rgb_colors); // converts HSB to RGB
  postColors(rgb_colors);
}


//+=============================================================================
// The repeating section of the code
//
void  loop ( )
{
  if (Serial.available() > 0) {

    uint8_t incomingByte = Serial.read();

    Serial.println("Received: " + incomingByte);

    if (incomingByte == 'R')
    {
      health = 500;
      livesCounter++;

      for (int i = 0; i < 500; i++)
      {
        hue = map(i, 0, 500, 0, 145);   // map health between red (dead) and green-blue
        getRGB(hue, 255, 255, rgb_colors);
        postColors(rgb_colors);
        delay(5); // 5*500 = 2.5s
      }

      health = 500;
      Serial.println("*L" + String(health) + "*");
      Serial.println("*S" + String(livesCounter) + "*");
      
    }

    else if (incomingByte == 'C')
    {
      // change hero type
      // simulate using a marvelous colour shade
      int temp_colors[3];
      int saturation = 255;                               // saturation is a number between 0 - 255
      int brightness = 255;                           // value is a number between 0 - 255


      for (int i = health; i > 0; i--)
      {
        hue = map(i, 0, 500, 0, 145);   // map health between red (dead) and green-blue
        getRGB(hue, saturation, brightness, temp_colors);
        postColors(temp_colors);
        delay(5);
      }

      for (int i = 0; i < health; i++)
      {
        hue = map(i, 0, 500, 0, 145);   // map health between red (dead) and green-blue
        getRGB(hue, saturation, brightness, temp_colors);
        postColors(temp_colors);
        delay(5);
      }

      if (heroIndex < 3)
      {
        heroIndex++;

      }
      else
      {
        heroIndex = 0;
      }
      Serial.println("*E" + String(heroes[heroIndex]) + "*");
    }
  }

  decode_results  results;        // Somewhere to store the results

  if (irrecv.decode(&results)) {  // Grab an IR code


    // All protocols have data
    Serial.print("Raw IR value = 0b");
    Serial.print(results.value, BIN);

    unsigned long value = results.value;
    unsigned long mask = 0b100000000000;
    value &= ~mask;

    //Serial.print("Value = 0b");
    //Serial.print(value, BIN);
    //Serial.println(";");

    if (health > 0)
    {
      if(value > 0 && value < 4)
      {
        Serial.println("*DV10*");
      }
      
      if (value == 1)
      {
        //Serial.println("received simple shot");
        health = max(0, health - 15);
      }
      if (value == 2)
      {
        //Serial.println("received hard shot");
        health = max(0, health - 30);
      }
      if (value == 3)
      {
        //Serial.println("received head shot");
        health = 0;

      }
      if (value == 4)
      {
        if(health < 500)
        {
          Serial.println("*HV10*");
        }
        health = min(500, health + 20);
      }
      if(health == 0)
      {
        // just died
        Serial.println("*MV10*");
      }
      
    }
    
    Serial.println("*L" + String(health) + "*");
    
    if (health > 0)
    {
      hue        = map(health, 0, 500, 0, 145);   // hue is a number between 0 and 360
      int saturation = 255;                               // saturation is a number between 0 - 255
      int brightness = 255;                           // value is a number between 0 - 255

      getRGB(hue, saturation, brightness, rgb_colors); // converts HSB to RGB
    }
    else
    {
      rgb_colors[0] = 0;
      rgb_colors[1] = 0;
      rgb_colors[2] = 0;
    }

    postColors(rgb_colors);

    irrecv.resume();              // Prepare for the next value
  }
}

