#pragma once

namespace Actor{

  /*
   *
   *
   *
   *
   */
  class Player{
  };

  class Weapon{
  
    public:
      Weapon(Action const& primaryAction, Action const& secondaryAction)
        : _primary(primaryAction), _secondary(secondaryAction)
      {
      }
      Action const& GetPrimary(){ return _primary;}
      Action const& GetSecondary(){ return _secondary;}

    private:
      Action const& _primary;
      Action const& _secondary;
  };

}
