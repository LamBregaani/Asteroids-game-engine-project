#include "Headers/EntityManager.h"
using GameEngine::EntityManager;
using GameEngine::EntityVec;
#include <vector>
#include <algorithm>
#include <iostream>
using std::cout;

EntityManager::EntityManager()
{

}

std::shared_ptr<Entity> EntityManager::CreateEntity()
{
	//Create an entity with a default tag
	auto e = CreateEntity("Default");
	return e;

}

std::shared_ptr<Entity> EntityManager::CreateEntity(const std::string& tag)
{
	//Create the entiy with the passed tag and a unique id
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities));
	//Add to the to be added vector
	m_toAdd.push_back(e);
	return e;
		
}

//Add and destroy entities
//Called at the end of the frame
void EntityManager::Update()
{
	
	//Add all the pending entites
	for (auto e : m_toAdd)
	{
		//Add the entity to the genral list
		m_entities.push_back(e);

		//Add the entity to the map of the given tag
		m_entityMap[e->getTag()].push_back(e);
	}

	for (auto& mapIt : m_entityMap)
	{
		auto& entityVec = mapIt.second;
		entityVec.erase(std::remove_if(entityVec.begin(), entityVec.end(),
			[](std::shared_ptr<Entity> const& e) {
				return e->isDestroyed();
			}), entityVec.end());
	}
	
	//m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
	//	[](std::shared_ptr<Entity> const& e) {
	//		return e->isDestroyed();
	//	}), m_entities.end());

	for (auto e : m_entities)
	{
		EntityVec::iterator it = m_entities.begin();

		if (it->get()->isDestroyed())
		{

			it->get()->OnDestory();
			it = m_entities.erase(it);
		}
		else
		{
			++it;
		}
	}

	m_toAdd.clear();
}

EntityVec& EntityManager::GetEntities()
{
	return m_entities;
}

EntityVec& EntityManager::GetEntities(const std::string& tag)
{
	EntityVec ex;

	if (m_entityMap.count(tag))
	{
		EntityVec& e = m_entityMap.at(tag);
		return e;
	}		

	return ex;
}

std::shared_ptr<Entity> EntityManager::GetEntityByID(int id)
{
	for (auto e : m_entities)
	{
		if (e->id() == id)
			return e;
	}

	return NULL;
}

std::shared_ptr<Entity> EntityManager::GetEntityByID(int id, std::string tag)
{
	if (m_entityMap.count(tag))
	{
		EntityVec& eVec = m_entityMap.at(tag);

		for (auto e : eVec)
		{
			if (e->id() == id)
				return e;
		}
	}

	return NULL;
}
