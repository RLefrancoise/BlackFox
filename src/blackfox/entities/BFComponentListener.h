#pragma once

#include <entt/entity/registry.hpp>
#include <entt/signal/sigh.hpp>

namespace BlackFox
{
	template<class Component>
	class BFComponentListener
	{
	public:
		using ComponentType = Component;
		
		entt::connection createConnection;
		entt::connection replaceConnection;
		entt::connection destroyConnection;

		virtual void listenCreate(entt::registry& r, entt::entity e)
		{
			onCreate(r, e, r.get<Component>(e));
		}

		virtual void listenUpdate(entt::registry& r, entt::entity e)
		{
			onReplace(r, e, r.get<Component>(e));
		}

		virtual void listenDestroy(entt::registry& r, entt::entity e)
		{
			onDestroy(r, e);
		}

		virtual void onCreate(entt::registry& r, entt::entity e, Component& c) = 0;
		virtual void onReplace(entt::registry& r, entt::entity e, Component& c) = 0;
		virtual void onDestroy(entt::registry& r, entt::entity e) = 0;

		BFComponentListener(entt::connection&& create, entt::connection&& replace, entt::connection&& destroy)
		: createConnection(create)
		, replaceConnection(replace)
		, destroyConnection(destroy)
		{}

		virtual ~BFComponentListener()
		{
			createConnection.release();
			replaceConnection.release();
			destroyConnection.release();
		}
	};

	template<class Component>
	class BFComponentListenerWithCallback : public BFComponentListener<Component>
	{
	public:
		using Super = BFComponentListener<Component>;
		using ClassType = BFComponentListenerWithCallback<Component>;

		typedef std::function<void(entt::registry&, entt::entity, Component&)> CreateCallback;
		typedef std::function<void(entt::registry&, entt::entity, Component&)> ReplaceCallback;
		typedef std::function<void(entt::registry&, entt::entity)> DestroyCallback;

		BFComponentListenerWithCallback(
				entt::registry* r, 
				CreateCallback createCallback, 
				ReplaceCallback replaceCallback, 
				DestroyCallback destroyCallback)
		: Super(
				r->on_construct<typename ClassType::ComponentType>().template connect<&ClassType::listenCreate>(*this),
				r->on_update<typename ClassType::ComponentType>().template connect<&ClassType::listenUpdate>(*this),
				r->on_destroy<typename ClassType::ComponentType>().template connect<&ClassType::listenDestroy>(*this))
		, m_onCreateCallback(createCallback)
		, m_onReplaceCallback(replaceCallback)
		, m_onDestroyCallback(destroyCallback)
		{}

		void onCreate(entt::registry& r, entt::entity e, Component& rb) override
		{
			m_onCreateCallback(r, e, rb);
		}

		void onReplace(entt::registry& r, entt::entity e, Component& rb) override
		{
			m_onReplaceCallback(r, e, rb);
		}

		void onDestroy(entt::registry& r, entt::entity e) override
		{
			m_onDestroyCallback(r, e);
		}

	private:
		CreateCallback m_onCreateCallback;
		ReplaceCallback m_onReplaceCallback;
		DestroyCallback m_onDestroyCallback;
	};
}