#include <transports/Software.h>

transport::Software::Software() {
}

void transport::Software::Queue(Action const &action) {
  _player->Accept(action);
}
