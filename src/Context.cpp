#include <Context.h>

int Context::_id = 0;

Context::Context(){
    this->id = ++_id;
}