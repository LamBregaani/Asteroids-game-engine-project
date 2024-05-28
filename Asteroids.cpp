#include "Scripts/Headers/Entity.h"
using Asteroids::Entity;

#include "Scripts/Headers/EntityManager.h"
using Asteroids::EntityManager;

#include "PlayerDeath.h"
using Asteroids::PlayerDeath;

#include <iostream>
using std::cout;

int Draw();

int main()
{
   EntityManager em;

   auto entity = em.CreateEntity("Player");

   em.Update();

   entity.get()->AddComponent<PlayerDeath>();

   entity.get()->Destroy();

   em.Update();

   Draw();

   return 0;
}


