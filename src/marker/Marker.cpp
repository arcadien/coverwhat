#include <Arduino.h>
#include <boarddefs.h>

#include <LowPower.h>

#include <IRremote.h>
#include <IRremoteInt.h>

#include <common/meta.h>



IRsend irsend;

const uint16_t ONE   = 0b00000000000001;
const uint16_t TWO   = 0b0000000000000010;
const uint16_t THREE = 0b0000000000000011;
const uint16_t HEAL  = 0b00000000000100;

#define IR_MESSAGE_LENGTH 14
#define LED 13

const byte _mainShotPin = 6;
const byte _secondShotPin = 5;
const byte _wakePin = 2;

// when no action is made for
// 10s (so, each 1000 interrupts)
// then the weapon goes to deep sleep
// until an action on a button wake it up
volatile uint16_t INACTIVITY_COUNTER = 0;

// we sleep 60ms when no fire
// we sleep 30ms when a fire occurend (around 28ms for a shot)
// so we have a freq of 1000/60, 16,666Hz
static const uint16_t COUNT_FOR_10S = 167; // 16,6 * 10

struct Weapon
{
  // bit position: action index
  // 0: damage
  // 1: healing
  //                    87654321
  //int8_t DPS_MASK = 0b00000000;

  int8_t DPS_MASK =   0b00000010;

  // main hit
  uint8_t FIRST_DPS = 50;

  // first action dommage per second
  uint8_t SECOND_DPS = 80; // health


};

#define SERIAL_DEBUG

#define HEARTBEAT

#define F_CPU 16000000U

#ifdef HEARTBEAT
#define PROCESS_HEARTBEAT TIMSK1 |= (1U << OCIE1A)
#define DISMISS_HEARTBEAT TIMSK1 &= ~(1U << OCIE1A)
void SetupHeartBeat()
{
  DISMISS_HEARTBEAT;
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0

  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // 16,66hz
  OCR1A = 936; // close to 16,66hz
}

ISR(TIMER1_COMPA_vect)
{
  INACTIVITY_COUNTER++;
}

#else
#define PROCESS_HEARTBEAT
#define DISMISS_HEARTBEAT
void SetupHeartBeat() {}
#endif

Weapon weapon();

uint16_t _damage;
uint16_t _heal;

void setup() {

  /*
    EventBuilder eb;

    eb.SetSource(0b00000001);
    eb.SetAmount(AMOUNT_10);
    eb.SetType(DAMAGE);
    _damage = eb.Build();

    eb.SetSource(0b00000001);
    eb.SetAmount(AMOUNT_10);
    eb.SetType(_HEAL);
    _heal = eb.Build();
  */
  _damage = ONE;
  _heal = HEAL;

#ifdef SERIAL_DEBUG
  Serial.begin(115200);
#endif

  pinMode(_mainShotPin, INPUT_PULLUP);
  pinMode(_secondShotPin, INPUT_PULLUP);
  pinMode(_wakePin, INPUT_PULLUP);

  //digitalWrite(_mainShotPin, HIGH);
  //digitalWrite(_mainShotPin, HIGH);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

#ifdef SERIAL_DEBUG
  Serial.print("CPU freq: ");
  Serial.println(F_CPU);
  Serial.println("Ready");
#endif

  SetupHeartBeat();

}

void send(uint16_t code)
{
  unsigned long time;
  digitalWrite(LED, HIGH);
  time = millis();
  irsend.sendRC5(code, IR_MESSAGE_LENGTH);
  unsigned long duration =  millis() - time;
  Serial.print("message duration: ");
  Serial.print(duration);
  Serial.println("ms");

  digitalWrite(LED, LOW);
}

void Print(const char* content)
{
#ifdef SERIAL_DEBUG
  Serial.println(content);
  delay(2);
#endif
}

void wake() {}

void loop() {

  if (Serial.available() > 0)
  {
    Serial.read();
    send(_damage);
  }

  DISMISS_HEARTBEAT;

  auto _mainIsPushed = (digitalRead(_mainShotPin) == LOW);
  auto _healIsPushed = (digitalRead(_secondShotPin) == LOW);

  // as a shot has around 28ms duration,
  // sleep 30ms if a fire occur, 60ms otherwise
  // to stay consistent
  auto sleepTime = SLEEP_60MS;

  if (_mainIsPushed)
  {
    INACTIVITY_COUNTER = 0;
    send(_damage);
    Print("d");
    sleepTime = SLEEP_30MS;

    // a shot last 28ms,
    // the sleep time is then 30ms
    // versus 60 ms without shot.
    // we add 2ms here to have
    // better time alignment
    delay(2);
  }
  else if (_healIsPushed)
  {
    INACTIVITY_COUNTER = 0;
    send(_heal);
    Print("h");
    sleepTime = SLEEP_30MS;

    // a shot last 28ms,
    // the sleep time is then 30ms
    // versus 60 ms without shot.
    // we add 2ms here to have
    // better time alignment
    delay(2);

  }
  else
  {
    Serial.println(INACTIVITY_COUNTER);
    delay(2);

#if not defined(HEARTBEAT)
    INACTIVITY_COUNTER++;
#endif
    if (INACTIVITY_COUNTER >= COUNT_FOR_10S)
    {
      INACTIVITY_COUNTER = 0;

      Print("s");

      for (size_t blinkCounter = 3; blinkCounter > 0 ; --blinkCounter)
      {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
      }
      attachInterrupt (0, wake, LOW);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      detachInterrupt (0);
    }
  }
#if defined(HEARTBEAT)
  PROCESS_HEARTBEAT;
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_ON, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
#else
  LowPower.powerDown(sleepTime, ADC_OFF, BOD_OFF);
#endif
}
