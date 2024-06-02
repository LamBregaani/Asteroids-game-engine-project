#ifndef ASTEROIDS_COMPONENT_H
#define ASTEROIDS_COMPONENT_H

#include <string>
using std::string;

namespace GameEngine
{
   class Component
   {
   public:

      virtual void Update()
      {

      }

      virtual void LateUpdate()
      {

      }

      virtual void OnDestroy()
      {

      }
   };
}
#endif
