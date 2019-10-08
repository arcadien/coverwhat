#include <api/Actor.h>
#include <api/ITransport.h>

void transport::Software::Queue(Action const &action) {
  _player->Accept(action);
}

transport::ITransport::~ITransport(){}
transport::Dummy::~Dummy(){}
transport::Software::~Software(){}
