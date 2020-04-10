#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <fmt/format.h>
#include <imgui.h>

#include "BFDebug.h"

namespace BlackFox::Editor
{	
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

	protected:
		explicit IBFWindow(std::string title, const ImGuiWindowFlags flags = ImGuiWindowFlags_None, ImVec2 initialSize = ImVec2())
		: m_title{ std::move(title) }
		, m_flags { flags }
		, m_initialSize { initialSize }
		{
		}
		
		std::string m_title;
		ImGuiWindowFlags m_flags;
		ImVec2 m_initialSize;

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
				if(m_initialSize.x > 0 && m_initialSize.y > 0) ImGui::SetNextWindowSize(m_initialSize, ImGuiCond_FirstUseEver);
				if (ImGui::Begin(uniqueId(m_title).c_str(), &m_opened, m_flags))
				{
					ImGui::PushID(m_imguiId.c_str());
					drawContent();
					ImGui::PopID();
				}

				ImGui::End();
			}

			return m_opened;
		}

		[[nodiscard]] BFWindow* clone() const override = 0;

	protected:
		static std::string generateId()
		{
			const auto id = fmt::format("{}_{}", typeid(WindowType).hash_code(), ++m_windowIdGenerator[typeid(WindowType)]);
			print("Generate id {} for window {}", id, typeid(WindowType).name());
			
			return id;
		}

		[[nodiscard]] std::string uniqueId(const std::string& id) const
		{
			return fmt::format("{}##{}", id, m_imguiId);
		}
		
		explicit BFWindow(std::string title, const ImGuiWindowFlags flags = ImGuiWindowFlags_None, const ImVec2 initialSize = ImVec2())
		: IBFWindow(std::move(title), flags, initialSize)
		, m_opened{ true }
		, m_imguiId{ generateId() }
		{
		}
		
		virtual void drawContent() = 0;

		bool m_opened;
		std::string m_imguiId;
	};
}
