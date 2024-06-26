#ifndef ASTEROIDS_COLLIDER_H
#define ASTEROIDS_COLLIDER_H

#include "Component.h"
using Asteroids::Component;

#include "Vector2.h"
using Asteroids::Vector2;

namespace Asteroids
{
   class Collider : public Component
   {
   protected:
      Vector2 center;
   };

   class CircleCollider : public Collider
   {
   public:
      float radius = 0;
      CircleCollider(float r)
         : radius(r) {}
   };
}
#endif
