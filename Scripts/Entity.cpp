
#include "Headers/Entity.h"
using GameEngine::Entity;

Entity::Entity(const std::string& tag, std::size_t id)
	:m_tag(tag),
	m_id(id)
{
	
}

std::string& Entity::getTag()
{
	return m_tag;
}

bool Entity::isDestroyed()
{
	return m_isDestoryed;
}

void Entity::Destroy()
{
	m_isDestoryed = true;
}

void Entity::OnDestory()
{
	for (auto it : m_components)
		it.second->OnDestroy();
}

const size_t Entity::id()
{
	return m_id;
}