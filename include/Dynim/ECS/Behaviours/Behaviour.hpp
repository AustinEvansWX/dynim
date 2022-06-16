#pragma once

#include <functional>

namespace Dynim {

class Behaviour {
public:
  virtual void Start(void *app_ptr, void *entity_ptr){};
  virtual void Update(void *app_ptr, void *entity_ptr, double delta_time){};
};

} // namespace Dynim
