/*


*/

enum Type {
  DAMAGE, /* lower shield or health */
  SHIELD, /* restore or add shield  */
  HEAL    /* restore health         */
};

enum Amount {
  AMOUNT_1,
  AMOUNT_5,
  AMOUNT_10,
  AMOUNT_25,
  AMOUNT_50,
  AMOUNT_100,
  AMOUNT_250,
  AMOUNT_FULL
};

/*!

   A Message is composed of 11 bits.

     10 9 8 7     6 5 4   3 2 1    0
   |----------- | ----- | ----- | --- |
      source       type   amnt    sum

   @since v0.1
*/
class EventBuilder {
  public:
    void SetSource(uint8_t source);
    void SetType(Type type);
    void SetAmount(Amount amount);

    // return 16 bits where only 11 from 0
    // are relevant
    uint16_t Build();
};

/*!

   A Message is composed of 11 bits.

     10 9 8 7     6 5 4   3 2 1    0
   |----------- | ----- | ----- | --- |
      source       type   amnt    sum

   @since v0.1
*/
class EventDecoder {
  public:
    void SetEvent(uint16_t event);
    uint8_t GetSource();
    Type GetType();
    Amount GetAmount();
    bool Check();
};




