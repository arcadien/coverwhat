#include <api/Actor.h>
#include <api/ITransport.h>
#include <api/Meta.h>
namespace Weapons {

class Vampire : public Actor::Weapon {
public:
  Vampire(transport::ITransport &transport)
      : Actor::Weapon(transport, Meta::Actions::DAMAGE5, Meta::Actions::HEAL5) {
  }
};

}; // namespace Weapons
