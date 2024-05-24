#ifndef ASTEROIDS_ENTITY_MANAGER_H
#define ASTEROIDS_ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"
using Asteroids::Entity;
#include <map>
#include <string>

namespace Asteroids
{
	typedef std::vector	<std::shared_ptr<Entity>> EntityVec;
	typedef std::map	<std::string, EntityVec> EntityMap;

	class EntityManager
	{
		EntityVec m_entities;
		EntityVec m_toAdd;
		EntityMap m_entityMap;
		std::size_t m_totalEntities = 0;

	public:

		EntityManager();
		void Update();
		std::shared_ptr<Entity> CreateEntity();
		std::shared_ptr<Entity> CreateEntity(const std::string& tag);
		//Returns all entites
		EntityVec& GetEntities();
		//Returns all entities with the passed tag
		EntityVec& GetEntities(const std::string& tag);

		//Returns the entity with the passed id
		std::shared_ptr<Entity> GetEntityByID(int id);
		//Returns the entity with the passed id and tag
		std::shared_ptr<Entity> GetEntityByID(int id, std::string tag);
	};
}
#endif
