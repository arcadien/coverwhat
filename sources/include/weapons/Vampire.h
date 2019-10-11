#include <actors/Weapon.h>
#include <api/ITransport.h>
#include <api/Meta.h>
namespace Weapons {

class Vampire : public actors::Weapon {
public:
  Vampire(transport::ITransport &transport)
      : actors::Weapon(transport, Meta::Actions::DAMAGE5,
                       Meta::Actions::HEAL5) {
  }
};

}// namespace Weapons
