#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <fmt/format.h>
#include <imgui.h>

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
		
		virtual bool draw() = 0;
		
		[[nodiscard]] virtual IBFWindow* clone() const = 0;
		
		[[nodiscard]] virtual const std::string& title() const { return m_title; }
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
	class BFWindow : public IBFWindow
	{
	public:
		//No copy
		BFWindow(const BFWindow&) = delete;
		BFWindow& operator=(const BFWindow&) = delete;

		//Move
		BFWindow(BFWindow&&) = default;
		BFWindow& operator=(BFWindow&&) = default;
		
		virtual ~BFWindow() noexcept = default;
		bool draw() override
		{
			if (m_opened)
			{
				//Set initial size if needed
				if(m_data.initialSize.x > 0 && m_data.initialSize.y > 0) ImGui::SetNextWindowSize(m_data.initialSize, ImGuiCond_FirstUseEver);

				//Set window size
				if(!hasFlag(m_data.flags, ImGuiWindowFlags_AlwaysAutoResize)) ImGui::SetNextWindowSize(m_data.size, ImGuiCond_Always);

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
							m_opened = drawContent();
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
							m_opened = drawContent();
							ImGui::PopID();
						}
					}

					ImGui::End();
				}
			}

			return m_opened;
		}

		[[nodiscard]] BFWindow* clone() const override = 0;

	protected:
		static std::string generateId()
		{
			const auto id = fmt::format("{}_{}", typeid(WindowType).hash_code(), ++m_windowIdGenerator[typeid(WindowType)]);
			BF_PRINT("Generate id {} for window {}", id, typeid(WindowType).name())
			
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
		
		virtual bool drawContent() = 0;

		bool m_opened;
		bool m_modalOpened;
		std::string m_imguiId;
	};
}
