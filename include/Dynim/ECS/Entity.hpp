#pragma once

#include "Dynim/ECS/Behaviours/Behaviour.hpp"

#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Dynim {

typedef std::unordered_map<std::type_index, void *> TypeMap;

class Entity {
public:
  template <typename T>
  inline T *GetComponent() {
    TypeMap::iterator component = m_Components.find(typeid(T));
    if (component != m_Components.end()) {
      return (T *)component->second;
    } else {
      return nullptr;
    }
  }

  template <typename T>
  inline void AddComponent(T *component) { m_Components[typeid(T)] = component; }

  inline std::vector<Behaviour *> GetBehaviours() const { return m_Behaviours; }
  inline void AddBehaviour(Behaviour *behaviour) { m_Behaviours.push_back(behaviour); }

private:
  TypeMap m_Components;
  std::vector<Behaviour *> m_Behaviours;
};

} // namespace Dynim
