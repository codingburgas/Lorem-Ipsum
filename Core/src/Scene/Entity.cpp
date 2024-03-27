#include "pch.h"
#include "Entity.h"

namespace Core {

	Entity::Entity(std::shared_ptr<Scene> scene)
	{
		m_Scene = scene;
		m_Entity = m_Scene->m_Registry.create();
		m_Scene->m_Entities.push_back(std::make_shared<Entity>(*this));
	}
}