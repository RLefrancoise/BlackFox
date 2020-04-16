#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <fmt/format.h>
#include <imgui.h>
#include <entt/signal/emitter.hpp>

#include "BFDebug.h"
#include "BFUtils.h"

namespace BlackFox::Editor
{	
	struct BFWindowData
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		bool isModal = false;
		ImVec2 initialSize = ImVec2();
		ImVec2 size = ImVec2(400, 300);
		ImVec2 minSize = ImVec2();
		ImVec2 maxSize = ImGui::GetIO().DisplaySize;
	};
	
	class IBFWindow
	{
	public:
		typedef std::shared_ptr<IBFWindow> Ptr;

		IBFWindow() = delete;
		
		//No copy
		IBFWindow(const IBFWindow&) = delete;
		IBFWindow& operator=(const IBFWindow&) = delete;

		//Move
		IBFWindow(IBFWindow&&) = default;
		IBFWindow& operator=(IBFWindow&&) = default;
		
		virtual ~IBFWindow() = default;
		
		virtual bool draw(float delta) = 0;
		
		[[nodiscard]] virtual IBFWindow* clone() const = 0;
		
		[[nodiscard]] const std::string& title() const { return m_title; }
		void title(const std::string& title) { m_title = title; }
		[[nodiscard]] const BFWindowData& data() const { return m_data; }
		void data(const BFWindowData& data) { m_data = data; }

	protected:
		explicit IBFWindow(std::string title, const BFWindowData& data)
		: m_title{std::move(title)}
		, m_data{data}
		{
		}
		
		std::string m_title;
		BFWindowData m_data;

		static std::unordered_map<std::type_index, unsigned int> m_windowIdGenerator;
	};
	
	template<typename WindowType>
	class BFWindow : public IBFWindow, public entt::emitter<WindowType>
	{
	public:

		/// <summary>
		/// Window closed event
		/// </summary>
		struct BFWindowClosedEvent{};
		
		//No copy
		BFWindow(const BFWindow&) = delete;
		BFWindow& operator=(const BFWindow&) = delete;

		//Move
		BFWindow(BFWindow&&) = default;
		BFWindow& operator=(BFWindow&&) = default;
		
		virtual ~BFWindow() noexcept = default;
		bool draw(const float delta) override
		{
			if (m_opened)
			{
				//Set initial size if needed
				if(m_data.initialSize.x > 0 && m_data.initialSize.y > 0) ImGui::SetNextWindowSize(m_data.initialSize, ImGuiCond_FirstUseEver);

				//Set window size
				if(!hasFlag(m_data.flags, ImGuiWindowFlags_AlwaysAutoResize)) ImGui::SetNextWindowSize(m_data.size, ImGuiCond_Always);

				//Set size constraints
				ImGui::SetNextWindowSizeConstraints(m_data.minSize, m_data.maxSize);
				
				if(m_data.isModal)
				{
					if(!m_modalOpened)
					{
						ImGui::OpenPopup(uniqueId(m_title).c_str());
						m_modalOpened = true;
					}
					
					if(ImGui::BeginPopupModal(uniqueId(m_title).c_str(), &m_opened, m_data.flags))
					{
						if (m_opened)
						{
							ImGui::PushID(m_imguiId.c_str());
							m_opened = drawContent(delta);
							ImGui::PopID();
						}

						if(!m_opened)
						{
							m_modalOpened = false;
						}
						
						ImGui::EndPopup();
					}
				}
				else
				{
					if (ImGui::Begin(uniqueId(m_title).c_str(), &m_opened, m_data.flags))
					{
						if (m_opened)
						{
							ImGui::PushID(m_imguiId.c_str());
							m_opened = drawContent(delta);
							ImGui::PopID();
						}
					}

					ImGui::End();
				}
			}

			//If window is closed, publish window closed event
			if(!m_opened)
			{
				static_cast<entt::emitter<WindowType>*>(this)->template publish<BFWindowClosedEvent>();
			}
			
			return m_opened;
		}

		[[nodiscard]] BFWindow* clone() const override = 0;

		template<typename EventType>
		typename entt::emitter<WindowType>::template connection<EventType> connect(const std::function<void(const EventType&, BFWindow<WindowType>&)>& fnc)
		{
			return on<EventType>(fnc);
		}

		template<typename EventType>
		typename entt::emitter<WindowType>::template connection<EventType> connectOnce(const std::function<void(const EventType&, BFWindow<WindowType>&)>& fnc)
		{
			return once<EventType>(fnc);
		}

		template<typename EventType>
		void detach(const typename entt::emitter<WindowType>::template connection<EventType>& conn)
		{
			erase(conn);
		}

		template<typename EventType>
		void detachListeners()
		{
			static_cast<entt::emitter<WindowType>*>(this)->template clear<EventType>();
		}
		
		void detachAllListeners()
		{
			static_cast<entt::emitter<WindowType>*>(this)->clear();
		}

	protected:
		static std::string generateId()
		{
			const auto id = fmt::format("{}_{}", typeid(WindowType).hash_code(), ++m_windowIdGenerator[typeid(WindowType)]);
			BF_PRINT("Generate id {} for window {}", id, typeid(WindowType).name());
			
			return id;
		}

		[[nodiscard]] std::string uniqueId(const std::string& id) const
		{
			return fmt::format("{}##{}", id, m_imguiId);
		}
		
		explicit BFWindow(const std::string& title, const BFWindowData& data = BFWindowData())
		: IBFWindow(title, data)
		, m_opened{ true }
		, m_modalOpened{ false }
		, m_imguiId{ generateId() }
		{
		}
		
		virtual bool drawContent(float delta) = 0;

		bool m_opened;
		bool m_modalOpened;
		std::string m_imguiId;
	};
}
