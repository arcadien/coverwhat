#pragma once

namespace hardware
{
/*
 * Hardware abstraction layer 
*/
template<typename Impl>
class Hardware{
  private:
    Impl impl_;

  public:
  void sleepMs(uint8_t seconds){
    impl_.sleepMs(seconds);
  }

};
}
