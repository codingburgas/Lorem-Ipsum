#pragma once
#include "pch.h"
#include <entt.hpp>
#include <box2d/box2d.h>

namespace Core {
	class Entity;
	
	/// @brief A scene is a container of entities and components
	class Scene
	{
	public:
		/// @brief Create a scene
		/// @param name The name of the scene
		Scene(std::string name = "New Scene") {}
		~Scene() = default;

		/// @brief Get the entity
		/// @tparam T The type of the component
		/// @return The created entity
		template<typename T>
		auto GetEntities()
		{
			std::vector<std::shared_ptr<Entity>> entitesWithComponent;
			
			for (auto& entity : m_Entities)
			{
				if (m_Registry.try_get<T>(entity->GetNativeEntity()))
				{
					entitesWithComponent.push_back(entity);
				}
			}

			return entitesWithComponent;
		}

		/// @brief Get the name of the scene
		std::string GetName() const { return m_SceneName; }

		/// @brief Set the name of the scene
		/// @param name The name of the scene
		void SetName(std::string name) { m_SceneName = name; }

		void InitPhysicsWorld(float gravityX, float gravityY);
		std::shared_ptr<b2World> GetPhysicsWorld() { return m_PhysicsWorld; }

		void PhysicsUpdate();
	private:
		std::string m_SceneName;
		entt::registry m_Registry;
		std::vector<std::shared_ptr<Entity>> m_Entities;
		
		std::shared_ptr<b2World> m_PhysicsWorld;

		friend class Entity;
	};
}
