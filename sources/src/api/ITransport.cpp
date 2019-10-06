#include <api/Actor.h>
#include <api/ITransport.h>

void transport::Software::Queue(Action const &action) {
  _player->Accept(action);
}
