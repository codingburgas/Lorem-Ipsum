#pragma once
#include "pch.h"

#include <raylib.h>
#include <glm/glm.hpp>
#include "Script/NativeScript.h"
#include <box2d/box2d.h>

namespace Core {
	/// @brief Tag component for entities
	struct TagComponent
	{
		std::string Tag;

		TagComponent(std::string tag)
		{
			Tag = tag;
		}
	};

	/// @brief Transform component for entities (position and rotation)
	struct TransformComponent
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;
		float Roundness = 0.0f;
		glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

		TransformComponent(glm::vec3 position, glm::vec3 scale, float rotation, float roundness)
		{
			Position = position;
			Scale = scale;
			Rotation = rotation;
			Roundness = roundness;
		}
	};

	struct NativeScriptComponent
	{
		std::shared_ptr<NativeScript> Instance = nullptr;

		NativeScriptComponent(std::shared_ptr<NativeScript> instance, std::shared_ptr<Entity> entity)
		{
			Instance = instance;
			Instance->m_Entity = entity;
		}
	};

	struct ColorComponent
	{
		glm::vec4 Color = { 255, 255, 255, 255 };

		ColorComponent() = default;
		
		ColorComponent(glm::vec4 color)
		{
			Color.r = round(color.r * 255);
			Color.g = round(color.g * 255);
			Color.b = round(color.b * 255);
			Color.a = round(color.a * 255);
		}
	};

	struct Box2DColliderComponent
	{
		glm::vec2 Size = { 1.0f, 1.0f };
		glm::vec2 Offset = { 0.0f, 0.0f };

		float Density = 1.0f;
		float Friction = 0.5f;

		Box2DColliderComponent() = default;
	};

	struct RidgetBody2DComponent
	{
		b2BodyType Type = b2_staticBody;
		bool FixedRotation = false;

		b2Body* Body = nullptr;

		RidgetBody2DComponent(b2BodyType type, bool fixedRotation)
		{
			Type = type;
			FixedRotation = fixedRotation;
		}
	};

	struct SpriteComponent
	{
		std::shared_ptr<Texture2D> Texture = nullptr;

		SpriteComponent(std::shared_ptr<Texture2D> texture)
		{
			Texture = texture;
		}
	};

	struct UIComponent
	{
		std::string Text;
		glm::vec4 Color;
		uint32_t TextSize;
		bool IsSecure = false;
		std::string FontType;

		UIComponent() = default;
		
		UIComponent(std::string text, glm::vec4 color, uint32_t textSize, std::string fontType = "regular", bool isSecure = false)
		{
			Text = text;
			TextSize = textSize;
			
			Color.r = round(color.r * 255);
			Color.g = round(color.g * 255);
			Color.b = round(color.b * 255);
			Color.a = round(color.a * 255);

			IsSecure = isSecure;

			FontType = fontType;
		}
	};

	enum class UIType
	{
		NONE = 0,
		BUTTON,
		INPUT,
		TEXT,
		AVATAR
	};

	struct UITypeComponent
	{
		UIType Type = UIType::NONE;

		UITypeComponent(UIType type)
		{
			Type = type;
		}
	};

	struct UIBorderComponent
	{
		glm::vec4 Color;

		UIBorderComponent() = default;
		UIBorderComponent(glm::vec4 color)
		{
			Color.r = round(color.r * 255);
			Color.g = round(color.g * 255);
			Color.b = round(color.b * 255);
			Color.a = round(color.a * 255);
		}
	};
}
