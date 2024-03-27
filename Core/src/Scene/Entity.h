#pragma once
#include "pch.h"
#include "Scene.h"

namespace Core
{
	struct NativeScriptComponent;
}

namespace Core {
	/// @brief An entity is a container of components	
	class Entity
	{
	public:
		/// @brief Create an entity
		/// @param scene The scene the entity belongs to 
		Entity(std::shared_ptr<Scene> scene);
		~Entity() = default;

		/// @brief Add a component to the entity
		/// @tparam T The type of the component
		/// @tparam Args The arguments to pass to the component constructor
		/// @param args The arguments to pass to the component constructor	
		template<typename T, typename... Args>
		void AddComponent(Args... args)
		{
			m_Scene->m_Registry.emplace<T>(m_Entity, args...);
		}
		

		/// @brief Get a component from the entity
		/// @tparam T The type of the component
		template<typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry.erase<T>(m_Entity);
		}

		/// @brief Get a native entitiy
		/// @return The native entity
		entt::entity GetNativeEntity() const
		{
			return m_Entity;
		}

		/// @brief Destroy an entity
		void Destroy()
		{
			m_Scene->m_Registry.destroy(m_Entity);
		}
		
		/// @brief Get a component from an entity
		/// @tparam T The type of the component
		/// @return The component 
		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_Entity);
		}

		
		/// @brief Check if an entity has a component
		/// @tparam T The type of the component
		/// @return True if the entity has the component, false otherwise
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.try_get<T>(m_Entity) != nullptr;
		}

	private:
		std::shared_ptr<Scene> m_Scene;
		entt::entity m_Entity;
	};
}
