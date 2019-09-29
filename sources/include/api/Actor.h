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

    private:
      Action const& _primary;
      Action const& _secondary;
  };

}
