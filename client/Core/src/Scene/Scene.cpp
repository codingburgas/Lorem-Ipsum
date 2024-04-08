#include "pch.h"
#include "Scene.h"
#include "Components.h"

namespace Core 
{
	void Scene::InitPhysicsWorld(float gravityX, float gravityY)
	{
		m_PhysicsWorld.reset(new b2World(b2Vec2(gravityX, gravityY)));

		for(auto& entity: m_Registry.view<RidgetBody2DComponent, TransformComponent>())
		{
			RidgetBody2DComponent& ridgetBody = m_Registry.get<RidgetBody2DComponent>(entity);
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

			b2BodyDef bodyDef;
		 
			bodyDef.type = ridgetBody.Type;
			bodyDef.position.Set(transform.Position.x, transform.Position.y);
		 
			bodyDef.angle = transform.Rotation;
			bodyDef.fixedRotation = ridgetBody.FixedRotation;
		 
			ridgetBody.Body = m_PhysicsWorld->CreateBody(&bodyDef);

			if(m_Registry.try_get<Box2DColliderComponent>(entity))
			{
				Box2DColliderComponent& collider = m_Registry.get<Box2DColliderComponent>(entity);

				b2PolygonShape shape;
				shape.SetAsBox(collider.Size.x * transform.Scale.x / 2, collider.Size.y * transform.Scale.y / 2, b2Vec2(transform.Scale.x / 2, transform.Scale.y / 2), 0.0f);
			
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = collider.Density;
				fixtureDef.friction = collider.Friction;
				ridgetBody.Body->CreateFixture(&fixtureDef);
			}
		}
	}

	void Scene::PhysicsUpdate()
	{
		m_PhysicsWorld->Step(1.0f / 60.0f, 6, 2);

		for(auto& entity: m_Registry.view<RidgetBody2DComponent, TransformComponent>())
		{
			RidgetBody2DComponent& ridgetBody = m_Registry.get<RidgetBody2DComponent>(entity);
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

			transform.Position.x = ridgetBody.Body->GetPosition().x;
			transform.Position.y = ridgetBody.Body->GetPosition().y;
			transform.Rotation = ridgetBody.Body->GetAngle();
		}
	}
}
