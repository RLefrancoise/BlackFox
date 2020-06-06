#pragma once

#include <entt/entity/registry.hpp>

namespace BlackFox
{
	template<class Component>
	class BFComponentListener
	{
	public:
		using ComponentType = Component;

		virtual void onCreate(entt::entity e, entt::registry& r, Component& c) = 0;
		virtual void onReplace(entt::entity e, entt::registry& r, Component& c) = 0;
		virtual void onDestroy(entt::entity e, entt::registry& r) = 0;
	};

	template<class Component>
	class BFComponentListenerWithCallback : public BFComponentListener<Component>
	{
	public:
		typedef std::function<void(entt::entity, entt::registry&, Component&)> CreateCallback;
		typedef std::function<void(entt::entity, entt::registry&, Component&)> ReplaceCallback;
		typedef std::function<void(entt::entity, entt::registry&)> DestroyCallback;

		BFComponentListenerWithCallback(CreateCallback createCallback, ReplaceCallback replaceCallback, DestroyCallback destroyCallback)
			: m_onCreateCallback(createCallback)
			, m_onReplaceCallback(replaceCallback)
			, m_onDestroyCallback(destroyCallback)
		{
		}

		void onCreate(entt::entity e, entt::registry& r, Component& rb) override
		{
			m_onCreateCallback(e, r, rb);
		}

		void onReplace(entt::entity e, entt::registry& r, Component& rb) override
		{
			m_onReplaceCallback(e, r, rb);
		}

		void onDestroy(entt::entity e, entt::registry& r) override
		{
			m_onDestroyCallback(e, r);
		}

	private:
		CreateCallback m_onCreateCallback;
		ReplaceCallback m_onReplaceCallback;
		DestroyCallback m_onDestroyCallback;
	};
}