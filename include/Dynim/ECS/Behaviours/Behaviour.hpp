#pragma once

#include <functional>

namespace Dynim {

class Behaviour {
public:
  inline void OnStart(std::function<void(void *app)> on_start_callback) { m_On_Start_Callback = on_start_callback; };
  inline void Start(void *app) {
    if (m_On_Start_Callback == nullptr) {
      return;
    }
    m_On_Start_Callback(app);
  };

  inline void OnUpdate(std::function<void(void *app, double delta_time)> on_update_callback) { m_On_Update_Callback = on_update_callback; };
  inline void Update(void *app, double delta_time) {
    if (m_On_Update_Callback == nullptr) {
      return;
    }
    m_On_Update_Callback(app, delta_time);
  };

private:
  std::function<void(void *app)> m_On_Start_Callback;
  std::function<void(void *app, double delta_time)> m_On_Update_Callback;
};

} // namespace Dynim
