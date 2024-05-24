#ifndef ASTEROIDS_ENTITY_H
#define ASTEROIDS_ENTITY_H

#include <unordered_map>
using std::unordered_map;

#include <typeinfo>
using std::type_info;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cerr;

#include "Component.h"

namespace Asteroids
{
   class Entity
   {
      std::size_t	m_id = 0;
      std::string	m_tag = "Default";

      //Whether the entity is marked as destoryed
      bool	m_isDestoryed = false;

      unordered_map<string, Component*> components;

      Entity(const std::string& tag, std::size_t id);

      friend class EntityManager;

   public:

      std::string & getTag();
      bool isDestroyed();
      const size_t id();

      void Destroy();

      void OnDestory();

      template <class T>
      T* AddComponent(T *component)
      {
         string name = typeid(component).name();

         cout << "Existing component type is: " << name << "\n";

         if (components.count(name))
         {
            cerr << "Component already added";
            return nullptr;
         }
         else
         {
            cout << "Adding existing component\n";
            components.emplace(name, component);

            if (components.find(name) == components.end())
            {
               cout << "Component not added\n";
               return nullptr;
            }
            
            cout << "Added component successfully\n";

            

            return component;
         }

         return nullptr;
      }

      template <class T>
      T* AddComponent()
      {
         string name = typeid(T*).name();

         cout << "Component type is: " << name << "\n";

         if (components.count(name))
         {
            cerr << "Component already added";
            return nullptr;
         }
         else
         {

            T *component = new T();

            cout << "Adding component\n";
            components.emplace(name, component);

            if (components.find(name) == components.end())
            {
               cout << "Component not added\n";
               return nullptr;
            }

            cout << "Added component successfully\n";

            return component;
         }

         return nullptr;
      }

      template <class T>
      T *GetComponent()
      {
         string name = typeid(T*).name();

         if (components.find(name) == components.end())
         {
            cerr << "Component not found";
            return nullptr;
         }
         else
            return (T*)components.at(name);
      }
   };
}
#endif
