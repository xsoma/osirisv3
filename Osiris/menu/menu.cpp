#include "menu.h"
#include "keydefs.h"

#include "images/menu/background_title.h"
#include "images/menu/tab_rage_icon.h"
#include "images/menu/tab_legit_icon.h"
#include "images/menu/tab_visuals_icon.h"
#include "images/menu/tab_kreedz_icon.h"
#include "images/menu/tab_misc_icon.h"
#include "images/menu/tab_configs_icon.h"
#include "images/menu/tab_console_icon.h"
#include "images/menu/wpn_pistols_icon.h"
#include "images/menu/wpn_rifles_icon.h"
#include "images/menu/wpn_snipers_icon.h"
#include "images/menu/wpn_shotguns_icon.h"
#include "images/menu/wpn_smgs_icon.h"
#include "images/weapons/weapon_ak47.h"
#include "images/weapons/weapon_aug.h"
#include "images/weapons/weapon_awp.h"
#include "images/weapons/weapon_c4.h"
#include "images/weapons/weapon_deagle.h"
#include "images/weapons/weapon_elite.h"
#include "images/weapons/weapon_famas.h"
#include "images/weapons/weapon_fiveseven.h"
#include "images/weapons/weapon_flashbang.h"
#include "images/weapons/weapon_g3sg1.h"
#include "images/weapons/weapon_galil.h"
#include "images/weapons/weapon_glock18.h"
#include "images/weapons/weapon_hegrenade.h"
#include "images/weapons/weapon_knife.h"
#include "images/weapons/weapon_m249.h"
#include "images/weapons/weapon_m4a1.h"
#include "images/weapons/weapon_m3.h"
#include "images/weapons/weapon_mac10.h"
#include "images/weapons/weapon_mp5.h"
#include "images/weapons/weapon_p228.h"
#include "images/weapons/weapon_p90.h"
#include "images/weapons/weapon_scout.h"
#include "images/weapons/weapon_sg550.h"
#include "images/weapons/weapon_sg552.h"
#include "images/weapons/weapon_smokegrenade.h"
#include "images/weapons/weapon_tmp.h"
#include "images/weapons/weapon_ump45.h"
#include "images/weapons/weapon_usp.h"
#include "images/weapons/weapon_xm1014.h"
#include "images/defuser/defuser.h"
#include "../cheats/postprocessing/PostProccessing.h"
#include <shellapi.h>
#include <tchar.h>
#include <Hooks.h>
#include "../cheats/misc connection/misc conn s.h"
#include <Hacks/Misc.h>
#include <Config.h>
#include "../imgui/imgui_stdlib.h"
#include <GUI.h>
#include <InventoryChanger/InventoryChanger.h>
#include <imguiCustom.h>
#include <Hacks/Glow.h>
#include <Hacks/StreamProofESP.h>
#include <Hacks/Visuals.h>




#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

ImFont* g_pFontList[MAX_FONTS];
ImageInfo g_pImageList[MAX_IMAGES];



void CDrawList::AddLine(const ImVec2& a, const ImVec2& b, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddRectFilled(a, b + ImVec2(1, 1), col, 1.f);
}



void CDrawList::AddRect(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline, float rounding, int rounding_corners_flags, float thickness)
{
	if (rounding)
	{
		GImGui->CurrentWindow->DrawList->AddRect(a, b + ImVec2(1, 1), col, rounding, rounding_corners_flags, thickness);
	}
	else
	{
		AddLine(ImVec2(a.x, a.y), ImVec2(b.x, a.y), col);
		AddLine(ImVec2(b.x, a.y + 1), ImVec2(b.x, b.y), col);
		AddLine(ImVec2(a.x, b.y), ImVec2(b.x - 1, b.y), col);
		AddLine(ImVec2(a.x, a.y + 1), ImVec2(a.x, b.y - 1), col);
	}

	if (outline)
	{
		const auto col_outline = ImColor(0.00f, 0.00f, 0.00f, col.value.w);

		AddRect(a - ImVec2(1, 1), b + ImVec2(1, 1), col_outline, false, rounding, rounding_corners_flags, thickness);
		AddRect(a + ImVec2(1, 1), b - ImVec2(1, 1), col_outline, false, rounding, rounding_corners_flags, thickness);
	}
}

void CDrawList::AddRectCorner(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline)
{
	const auto line_w = (b.x - a.x) * 0.25f;
	const auto line_h = (b.y - a.y) * 0.25f;

	AddLine(ImVec2(a.x, a.y + 1), ImVec2(a.x, a.y + line_h), col);
	AddLine(ImVec2(a.x, a.y), ImVec2(a.x + line_w, a.y), col);
	AddLine(ImVec2(b.x - line_w, a.y), ImVec2(b.x, a.y), col);
	AddLine(ImVec2(b.x, a.y + 1), ImVec2(b.x, a.y + line_h), col);
	AddLine(ImVec2(a.x, b.y - line_h), ImVec2(a.x, b.y - 1), col);
	AddLine(ImVec2(a.x, b.y), ImVec2(a.x + line_w, b.y), col);
	AddLine(ImVec2(b.x - line_w, b.y), ImVec2(b.x, b.y), col);
	AddLine(ImVec2(b.x, b.y - line_h), ImVec2(b.x, b.y - 1), col);

	if (outline)
	{
		const auto col_outline = ImColor(0.00f, 0.00f, 0.00f, col.value.w);

		AddLine(ImVec2(a.x, a.y - 1), ImVec2(a.x + line_w - 1, a.y - 1), col_outline);
		AddLine(ImVec2(a.x + 2, a.y + 1), ImVec2(a.x + line_w - 1, a.y + 1), col_outline);
		AddLine(ImVec2(a.x + line_w, a.y - 1), ImVec2(a.x + line_w, a.y + 1), col_outline);

		AddLine(ImVec2(a.x - 1, a.y - 1), ImVec2(a.x - 1, a.y + line_h - 1), col_outline);
		AddLine(ImVec2(a.x + 1, a.y + 1), ImVec2(a.x + 1, a.y + line_h - 1), col_outline);
		AddLine(ImVec2(a.x - 1, a.y + line_h), ImVec2(a.x + 1, a.y + line_h), col_outline);

		AddLine(ImVec2(a.x - 1, b.y - line_h + 1), ImVec2(a.x - 1, b.y), col_outline);
		AddLine(ImVec2(a.x + 1, b.y - line_h + 1), ImVec2(a.x + 1, b.y - 1), col_outline);
		AddLine(ImVec2(a.x - 1, b.y - line_h), ImVec2(a.x + 1, b.y - line_h), col_outline);

		AddLine(ImVec2(a.x - 1, b.y + 1), ImVec2(a.x + line_w - 1, b.y + 1), col_outline);
		AddLine(ImVec2(a.x + 2, b.y - 1), ImVec2(a.x + line_w - 1, b.y - 1), col_outline);
		AddLine(ImVec2(a.x + line_w, b.y - 1), ImVec2(a.x + line_w, b.y + 1), col_outline);

		AddLine(ImVec2(b.x - line_w + 1, a.y - 1), ImVec2(b.x, a.y - 1), col_outline);
		AddLine(ImVec2(b.x - line_w + 1, a.y + 1), ImVec2(b.x - 1, a.y + 1), col_outline);
		AddLine(ImVec2(b.x - line_w, a.y - 1), ImVec2(b.x - line_w, a.y + 1), col_outline);

		AddLine(ImVec2(b.x + 1, a.y - 1), ImVec2(b.x + 1, a.y + line_h - 1), col_outline);
		AddLine(ImVec2(b.x - 1, a.y + 2), ImVec2(b.x - 1, a.y + line_h - 1), col_outline);
		AddLine(ImVec2(b.x - 1, a.y + line_h), ImVec2(b.x + 1, a.y + line_h), col_outline);

		AddLine(ImVec2(b.x + 1, b.y - line_h + 1), ImVec2(b.x + 1, b.y + 1), col_outline);
		AddLine(ImVec2(b.x - 1, b.y - line_h + 1), ImVec2(b.x - 1, b.y - 1), col_outline);
		AddLine(ImVec2(b.x - 1, b.y - line_h), ImVec2(b.x + 1, b.y - line_h), col_outline);

		AddLine(ImVec2(b.x - line_w + 1, b.y + 1), ImVec2(b.x, b.y + 1), col_outline);
		AddLine(ImVec2(b.x - line_w + 1, b.y - 1), ImVec2(b.x - 2, b.y - 1), col_outline);
		AddLine(ImVec2(b.x - line_w, b.y - 1), ImVec2(b.x - line_w, b.y + 1), col_outline);
	}
}

void CDrawList::AddRectFilled(const ImVec2& a, const ImVec2& b, const ImColor& col, float rounding, int rounding_corners_flags)
{
	GImGui->CurrentWindow->DrawList->AddRectFilled(a, b, col, rounding, rounding_corners_flags);
}

void CDrawList::AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left)
{
	GImGui->CurrentWindow->DrawList->AddRectFilledMultiColor(a, c, col_upr_left, col_upr_right, col_bot_right, col_bot_left);
}

void CDrawList::AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddQuad(a, b, c, d, col, thickness);
}

void CDrawList::AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddQuadFilled(a, b, c, d, col);
}

void CDrawList::AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddTriangle(a, b, c, col, thickness);
}

void CDrawList::AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddTriangleFilled(a, b, c, col);
}

void CDrawList::AddCircle(const ImVec2& centre, float radius, const ImColor& col, int num_segments, float thickness)
{
	GImGui->CurrentWindow->DrawList->AddCircle(centre, radius, col, num_segments, thickness);
}

void CDrawList::AddCircleFilled(const ImVec2& centre, float radius, const ImColor& col, int num_segments)
{
	GImGui->CurrentWindow->DrawList->AddCircleFilled(centre, radius, col, num_segments);
}

static void AddTextEx(ImVec2 pos, const ImColor& col, float wrap_width = 0.f, FontFlags_t flags = FontFlags_None, const char* fmt = NULL)
{
	if (!fmt || !strlen(fmt))
		return;

	const auto text_size = GImGui->Font->CalcTextSizeA(GImGui->Font->FontSize, FLT_MAX, wrap_width, fmt);
	const auto col_outline = ImColor(0.00f, 0.00f, 0.00f, col.value.w);

	if (flags & FontFlags_CenterX)
		pos.x -= text_size.x * 0.5f;

	if (flags & FontFlags_CenterY)
		pos.y -= text_size.y * 0.5f;

	GImGui->CurrentWindow->DrawList->PushTextureID(GImGui->IO.Fonts->TexID);

	if (flags & FontFlags_Shadow)
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 1), col_outline, fmt);

	if (flags & FontFlags_Outline)
	{
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(0, 1), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(0, 1), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 0), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(1, 0), col_outline, fmt);

		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(1, 1), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, -1), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos - ImVec2(-1, 1), col_outline, fmt);
		GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos + ImVec2(1, 1), col_outline, fmt);
	}

	GImGui->CurrentWindow->DrawList->AddText(GImGui->Font, GImGui->Font->FontSize, pos, col, fmt);
	GImGui->CurrentWindow->DrawList->PopTextureID();
}

void CDrawList::AddText(const ImVec2& pos, const ImColor& col, FontFlags_t flags, const char* fmt, ...)
{
	char buf[4096] = { '\0' };
	va_list vlist = nullptr;
	va_start(vlist, fmt);
	vsprintf_s(buf, fmt, vlist);
	va_end(vlist);

	AddTextEx(pos, col, 0, flags, buf);
}

void CDrawList::AddTextWrapped(const ImVec2& pos, const ImColor& col, float wrap_width, FontFlags_t flags, const char* fmt, ...)
{
	char buf[4096] = { '\0' };
	va_list vlist = nullptr;
	va_start(vlist, fmt);
	vsprintf_s(buf, fmt, vlist);
	va_end(vlist);

	AddTextEx(pos, col, wrap_width, flags, buf);
}

void CDrawList::AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, const ImColor& col)
{
	GImGui->CurrentWindow->DrawList->AddImage(user_texture_id, a, b, uv_a, uv_b, col);
}







bool CMenuPopupModal::Begin(std::string name, const ImVec2& size)
{
	ImGui::SetNextWindowSize(size);

	const auto flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
	const auto ret = ImGui::BeginPopupModal(name.c_str(), nullptr, flags);

	if (ret)
	{
		ImGui::Spacing(2);
		ImGui::SameLine(WINDOW_PADDING_SAMELINE);
		ImGui::BeginGroup();
	}

	return ret;
}

void CMenuPopupModal::End()
{
	ImGui::EndGroup();
	ImGui::EndPopup();
}

float CMenuPopupModal::GetItemWidth()
{
	return GImGui->CurrentWindow->Size.x - WINDOW_PADDING_SAMELINE * 2.f;
}

void CMenuPopupModal::Input(std::string name, char* buf, size_t buf_size)
{
	ImGui::Text(name.c_str());

	const auto item_width = GetItemWidth();
	const auto str_id = "##" + name;

	ImGui::SetNextItemWidth(item_width);
	ImGui::InputText(str_id.c_str(), buf, buf_size);

	ImGui::Spacing();
}

void CMenuPopupModal::Message(std::string message)
{
	const auto item_width = GetItemWidth();
	const auto text_size = GImGui->Font->CalcTextSizeA(GImGui->Font->FontSize, item_width, 0, message.c_str());

	ImGui::SameLine((item_width - text_size.x) * 0.5f);
	ImGui::Text(message.c_str());

	ImGui::Spacing();
}

bool CMenuPopupModal::Button(std::string name)
{
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());

	const auto ret = ImGui::Button(name.c_str(), ImVec2(106, 20));

	ImGui::PopStyleColor();
	ImGui::SameLine();

	return ret;
}





bool CMenuGui::Begin(std::string name, const ImVec2& size)
{
	ImVec2 size_const = size;

	size_const.x = std::min(size_const.x, GImGui->IO.DisplaySize.x);
	size_const.y = std::min(size_const.y, GImGui->IO.DisplaySize.y);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4());

	ImGui::SetNextWindowSizeConstraints(size_const, GImGui->IO.DisplaySize);
	ImGui::SetNextWindowSize(size, ImGuiCond_Once);
	ImGui::SetNextWindowPosCenter(ImGuiCond_FirstUseEver);

	const bool ret = ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);

	return ret;
}

void CMenuGui::BeginCanvas(std::string name, const ImVec2& size, bool border)
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, GImGui->Style.Colors[ImGuiCol_WindowBg]);
	ImGui::BeginChild(name.c_str(), size, border);
	ImGui::PopStyleColor();
}

void CMenuGui::BeginGroupBox(std::string name, const ImVec2& size, bool border)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	ImGui::BeginChildCustom(name.c_str(), size, border);
	ImGui::PopStyleVar();
}

void CMenuGui::BeginWidgetsGroup()
{
	ImGui::Spacing(WINDOW_WIDGETS_PADDING_SPACING);
	ImGui::SameLine(WINDOW_WIDGETS_PADDING_SAMELINE);
	ImGui::BeginGroup();
}

void CMenuGui::End()
{
	ImVec2 window_pos = GImGui->CurrentWindow->Pos;
	ImVec2 window_size = GImGui->CurrentWindow->Size;

	GImGui->CurrentWindow->DrawList->PushClipRectFullScreen();

	RectangleShadowSettings shadowSettings;
	shadowSettings.shadowColor = GImGui->Style.Colors[ImGuiCol_BorderShadow];
	ImGui::DrawRectangleShadowVerticesAdaptive(shadowSettings, window_pos, window_size);

	ImGui::End();
}

void CMenuGui::EndCanvas()
{
	ImGui::EndChild();
}

void CMenuGui::EndGroupBox()
{
	ImGui::EndChildCustom();
}

void CMenuGui::EndWidgetsGroup()
{
	ImGui::Spacing(3);
	ImGui::EndGroup();
}

void CMenuGui::SmallGroupBox(std::string name, const ImVec2& size, std::function<void()> widget_first, std::function<void()> widget_second)
{
	BeginGroupBox(name, size);

	std::string widgets_names[2] = { name + "widget_first", name + "widget_second" };

	ImGui::BeginChild(widgets_names[0].c_str(), ImVec2(size.x * 0.5f, size.y));
	ImGui::SetCursorPos(ImVec2(WINDOW_WIDGETS_PADDING_SAMELINE, 9));
	widget_first();
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild(widgets_names[1].c_str(), ImVec2(size.x - ImGui::GetCursorPosX(), size.y));
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + WINDOW_WIDGETS_PADDING_SAMELINE, 9));
	widget_second();
	ImGui::EndChild();

	EndGroupBox();
}

void CMenuGui::UnderBackground()
{
	ImVec2 background_pos = GImGui->CurrentWindow->Pos + ImVec2(0, GImGui->CurrentWindow->Size.y - WINDOW_UNDERGROUND_HEIGHT);
	ImVec2 background_size = ImVec2(GImGui->CurrentWindow->Size.x, WINDOW_UNDERGROUND_HEIGHT);

	DrawList->AddRectFilled(background_pos, background_pos + background_size, GImGui->Style.Colors[ImGuiCol_Tab]);
}

void CMenuGui::UnderContents()
{
	ImGui::PushFont(g_pFontList[Verdana_13px]);

	GImGui->CurrentWindow->DC.CursorPos = ImVec2(GImGui->CurrentWindow->Pos.x + 6,
		GImGui->CurrentWindow->Pos.y + GImGui->CurrentWindow->Size.y - 16);

	if (m_message.empty())
	{
		std::string hackinfo = "hook";
		ImGui::Text(hackinfo.c_str());
	}
	else
	{
		ImGui::Text(m_message.c_str());

		m_message.clear();
	}

	std::string url = "https://shonaxing.xyz";

	ImVec2 text_size = GImGui->Font->CalcTextSizeA(GImGui->Font->FontSize, FLT_MAX, 0, url.c_str());

	ImGui::SameLine(GImGui->CurrentWindow->Size.x - text_size.x - WINDOW_PADDING_SAMELINE * 0.5f);

	Link(url);

	ImGui::PopFont();
}

void CMenuGui::TabBackground()
{
	ImVec2 background_size = ImVec2(GImGui->CurrentWindow->Size.x, MENU_TAB_HEIGHT);

	DrawList->AddRectFilled(GImGui->CurrentWindow->Pos, GImGui->CurrentWindow->Pos + background_size, GImGui->Style.Colors[ImGuiCol_Tab]);

	ImGui::Image(g_pImageList[MenuTitleBg].data, ImVec2(g_pImageList[MenuTitleBg].size.x - 70.f, MENU_TAB_HEIGHT - 2));
}

bool CMenuGui::TabList(std::vector<TabWidgetsData>& data, int& selected, int& hovered)
{
	ImGui::SameLine(GImGui->CurrentWindow->Size.x / 3.5f);

	ImGuiStyle backup_style = GImGui->Style;

	GImGui->Style.ItemSpacing = ImVec2(0, 1);

	ImVec2 button_size = ImVec2((GImGui->CurrentWindow->Size.x - ImGui::GetCursorPosX()) / data.size(), MENU_TAB_HEIGHT);
	ImVec4 button_color = GImGui->Style.Colors[ImGuiCol_TabHovered];

	button_color.w = 0.00f;

	bool changed = false;

	ImGui::PushFont(g_pFontList[Verdana_16px]);

	for (size_t i = 0; i < data.size(); i++)
	{
		GImGui->Style.Colors[ImGuiCol_ButtonActive] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_TabHovered], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_ButtonHovered] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_TabHovered], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_Button] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_TabHovered], ImSaturate(data[i].fading_value));

		bool pressed_button = false;

		if (selected == static_cast<int>(i))
		{
			GImGui->Style.Colors[ImGuiCol_Button] = GImGui->Style.Colors[ImGuiCol_TabActive];
			GImGui->Style.Colors[ImGuiCol_ButtonHovered] = GImGui->Style.Colors[ImGuiCol_TabActive];
			GImGui->Style.Colors[ImGuiCol_ButtonActive] = GImGui->Style.Colors[ImGuiCol_TabActive];

			pressed_button = ImGui::ButtonTabsNormal(data[i].label.c_str(), button_size);
		}
		else if (hovered == static_cast<int>(i))
		{
			pressed_button = ImGui::ButtonTabsNormal(data[i].label.c_str(), button_size);
		}
		else
		{
			pressed_button = ImGui::ImageButtonTab(g_pImageList[i + IconsTabsOffset].data, button_size);
		}

		if (pressed_button)
		{
			changed = selected != static_cast<int>(i);
			selected = static_cast<int>(i);
		}

		if (ImGui::IsItemHovered())
		{
			hovered = static_cast<int>(i);

			data[i].fading_value = std::min(data[i].fading_value + GImGui->IO.DeltaTime * 6.f, 1.00f);
		}
		else
		{
			data[i].fading_value = std::max(data[i].fading_value - GImGui->IO.DeltaTime * 6.f, 0.00f);

			if (hovered == static_cast<int>(i))
				hovered = -1;
		}

		if (i < data.size() - 1)
			ImGui::SameLine();
	}

	ImGui::PopFont();

	GImGui->Style = backup_style;

	return changed;
}

bool CMenuGui::TabFeaturesList(std::vector<TabWidgetsData>& data, int& selected, int& hovered)
{
	ImGuiStyle backup_style = GImGui->Style;

	GImGui->Style.ItemSpacing = ImVec2(0, 1);
	GImGui->Style.Colors[ImGuiCol_Border] = ImColor();

	ImVec2 button_size = ImVec2(GImGui->CurrentWindow->Size.x / data.size(), 32);
	ImVec4 button_color = GImGui->Style.Colors[ImGuiCol_ChildBg];
	ImVec4 normal_text_color = GImGui->Style.Colors[ImGuiCol_FrameBgHovered];

	bool changed = false;

	ImGui::PushFont(g_pFontList[Verdana_16px]);

	for (size_t i = 0; i < data.size(); i++)
	{
		GImGui->Style.Colors[ImGuiCol_ButtonActive] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_ButtonHovered] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_Button] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_Text] = ImLerp(normal_text_color, GImGui->Style.Colors[ImGuiCol_FrameBgActive], ImSaturate(data[i].fading_value));

		bool pressed_button = false;

		if (selected == static_cast<int>(i))
		{
			GImGui->Style.Colors[ImGuiCol_Button] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_ButtonHovered] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_ButtonActive] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_Text] = GImGui->Style.Colors[ImGuiCol_FrameBgActive];

			pressed_button = ImGui::ButtonTabs(data[i].label.c_str(), button_size);
		}
		else if (hovered == static_cast<int>(i))
		{
			pressed_button = ImGui::ButtonTabs(data[i].label.c_str(), button_size);
		}
		else
		{
			pressed_button = ImGui::ButtonTabs(data[i].label.c_str(), button_size);
		}

		if (pressed_button)
		{
			changed = selected != static_cast<int>(i);
			selected = static_cast<int>(i);
		}

		if (ImGui::IsItemHovered())
		{
			hovered = static_cast<int>(i);

			data[i].fading_value = std::min(data[i].fading_value + GImGui->IO.DeltaTime * 6.f, 1.00f);
		}
		else
		{
			data[i].fading_value = std::max(data[i].fading_value - GImGui->IO.DeltaTime * 6.f, 0.00f);

			if (hovered == static_cast<int>(i))
				hovered = -1;
		}

		if (i < data.size() - 1)
			ImGui::SameLine();
	}

	ImGui::PopFont();

	GImGui->Style = backup_style;

	return changed;
}

bool CMenuGui::TabWeaponList(std::vector<TabWidgetsData>& data, int& selected, int& hovered)
{
	ImGuiStyle backup_style = GImGui->Style;

	GImGui->Style.ItemSpacing = ImVec2(0, 1);
	GImGui->Style.Colors[ImGuiCol_Border] = ImColor();

	ImVec2 button_size = ImVec2(GImGui->CurrentWindow->Size.x / data.size(), 32);
	ImVec4 button_color = GImGui->Style.Colors[ImGuiCol_ChildBg];
	ImVec4 normal_text_color = GImGui->Style.Colors[ImGuiCol_FrameBgHovered];

	bool changed = false;

	ImGui::PushFont(g_pFontList[Verdana_16px]);

	for (size_t i = 0; i < data.size(); i++)
	{
		GImGui->Style.Colors[ImGuiCol_ButtonActive] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_ButtonHovered] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_Button] = ImLerp(button_color, GImGui->Style.Colors[ImGuiCol_FrameBg], ImSaturate(data[i].fading_value));
		GImGui->Style.Colors[ImGuiCol_Text] = ImLerp(normal_text_color, GImGui->Style.Colors[ImGuiCol_FrameBgActive], ImSaturate(data[i].fading_value));

		bool pressed_button = false;

		if (selected == static_cast<int>(i))
		{
			GImGui->Style.Colors[ImGuiCol_Button] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_ButtonHovered] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_ButtonActive] = GImGui->Style.Colors[ImGuiCol_FrameBg];
			GImGui->Style.Colors[ImGuiCol_Text] = GImGui->Style.Colors[ImGuiCol_FrameBgActive];

			pressed_button = ImGui::ButtonTabs(data[i].label.c_str(), button_size);
		}
		else if (hovered == static_cast<int>(i))
		{
			pressed_button = ImGui::ButtonTabs(data[i].label.c_str(), button_size);
		}
		else
		{
			pressed_button = ImGui::ImageButtonBySize(g_pImageList[i + IconsWpnsOffset].data, button_size, g_pImageList[i + IconsWpnsOffset].size);
		}

		if (pressed_button)
		{
			changed = selected != static_cast<int>(i);
			selected = static_cast<int>(i);
		}

		if (ImGui::IsItemHovered())
		{
			hovered = static_cast<int>(i);

			data[i].fading_value = std::min(data[i].fading_value + GImGui->IO.DeltaTime * 6.f, 1.00f);
		}
		else
		{
			data[i].fading_value = std::max(data[i].fading_value - GImGui->IO.DeltaTime * 6.f, 0.00f);

			if (hovered == static_cast<int>(i))
				hovered = -1;
		}

		if (i < data.size() - 1)
			ImGui::SameLine();
	}

	ImGui::PopFont();

	GImGui->Style = backup_style;

	return changed;
}

void CMenuGui::TabSeparator()
{
	ImGuiStyle backup_style = GImGui->Style;

	GImGui->Style.ItemSpacing = ImVec2(0, 1);
	GImGui->Style.Colors[ImGuiCol_Separator] = backup_style.Colors[ImGuiCol_TabActive];

	ImGui::Separator(4);

	GImGui->Style = backup_style;
}

void CMenuGui::TabShadow(const ImVec2& pos, const ImVec2& size, const ImVec4& color)
{
	ImColor border_col_low_alpha = color;
	ImColor border_col_no_alpha = color;

	border_col_low_alpha.value.w = 0.45f;
	border_col_no_alpha.value.w = 0.00f;

	GImGui->CurrentWindow->DrawList->AddRectFilledMultiColor(pos, size, border_col_low_alpha, border_col_low_alpha, border_col_no_alpha, border_col_no_alpha);
}

void CMenuGui::SetID(const char* str_id)
{
	m_id = str_id;
}

void CMenuGui::SetChildSize(ImVec2& size)
{
	size.x = (GImGui->CurrentWindow->Size.x - WINDOW_PADDING_SAMELINE * 4.f) / 3.f;
	size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;
}

void CMenuGui::Text(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextV(fmt, args);
	va_end(args);
}

bool CMenuGui::Checkbox(bool* v, std::string label, std::string message)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::Checkbox(hashed_string.c_str(), v);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (ImGui::IsItemHovered())
		m_message = message;

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::Combo(int* v, std::string label, const char* items[], int size, std::string message, bool owned)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::Combo(hashed_string.c_str(), v, items, size, -1, owned);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (ImGui::IsItemHovered())
		m_message = message;

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::MultiCombo(bool* v, std::string label, const char* items[], int size, std::string message)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::MultiCombo(hashed_string.c_str(), items, v, size);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (ImGui::IsItemHovered())
		m_message = message;

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::Slider(float* v, std::string label, float min, float max, const char* format, float power, std::string message)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::SliderFloat(hashed_string.c_str(), v, min, max, format, power);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (ImGui::IsItemHovered())
		m_message = message;

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::Slider(int* v, std::string label, int min, int max, const char* format, std::string message)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::SliderInt(hashed_string.c_str(), v, min, max, format);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (ImGui::IsItemHovered())
		m_message = message;

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

static bool vector_getter(void* data, int id, const char** out_text)
{
	const auto& vector = *static_cast<std::vector<std::string>*>(data);
	*out_text = vector.at(id).c_str();
	return true;
};

bool CMenuGui::ListBox(const char* label, int* current_item, std::vector<std::string>& values, int height_in_items)
{
	ImGui::PushStyleColor(ImGuiCol_Header, ImGui::GetColorU32(ImGuiCol_FrameBg));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImGui::GetColorU32(ImGuiCol_FrameBg));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImGui::GetColorU32(ImGuiCol_FrameBg));

	const bool ret = ImGui::ListBox(label, current_item, vector_getter, &values, values.size(), height_in_items);

	ImGui::PopStyleColor(3);

	return ret;
}

void CMenuGui::Separator()
{
	ImGui::Spacing();
	ImGui::Separator(GImGui->CurrentWindow->Size.x - WINDOW_PADDING_SAMELINE);
	ImGui::Spacing();
}

void CMenuGui::Link(std::string url)
{
	static std::vector<LinkData> url_list;

	int id = -1;

	if (!url_list.empty())
	{
		for (size_t i = 0; i < url_list.size(); i++)
		{
			if (url_list[i].url.compare(url))
				continue;

			id = static_cast<int>(i);
			break;
		}
	}

	if (id == -1)
	{
		url_list.push_back(LinkData{ url, false, false });
		id = static_cast<int>(url_list.size()) - 1;
	}

	bool ret = false;

	for (size_t i = 0; i < url_list.size(); i++)
	{
		if (id == static_cast<int>(i))
			continue;

		if (url_list[i].hovered || url_list[i].clicked)
			ret = true;
	}

	ImGui::Text(url.c_str());

	if (ret)
		return;

	url_list[id].hovered = ImGui::IsItemHovered();

	if (url_list[id].hovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

		GImGui->CurrentWindow->Flags |= ImGuiWindowFlags_NoMove;

		if (ImGui::IsItemClicked(0))
			url_list[id].clicked = true;

		if (url_list[id].clicked && ImGui::IsMouseReleased(0))
		{
			ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
			url_list[id].clicked = false;
		}
	}
	else
	{
		GImGui->CurrentWindow->Flags &= ~ImGuiWindowFlags_NoMove;

		url_list[id].clicked = false;
	}
}



bool CMenuGui::Key(void* v, std::string label, bool owned)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::KeyButton(hashed_string.c_str(), v, owned);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}
bool CMenuGui::KeyToggle(KeyBind* v, std::string label, bool owned)
{

	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::KeyButtonToggle(hashed_string.c_str(), v, owned);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}
bool CMenuGui::KeyToggle(void* v, std::string label, bool owned)
{
	
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::KeyButtonToggle(hashed_string.c_str(), v, owned);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::KeyPress(void* v, std::string label, bool owned)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::KeyButtonPress(hashed_string.c_str(), v, owned);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

bool CMenuGui::ColorEdit(float* v, std::string label)
{
	std::string hashed_string = label + m_id;

	float& fading_value = FindWidgetsFadingValue(hashed_string);

	ImGui::PushStyleColor(ImGuiCol_Border, ImLerp(GImGui->Style.Colors[ImGuiCol_ChildBg],
		GImGui->Style.Colors[ImGuiCol_Border], ImSaturate(fading_value)));

	const bool ret = ImGui::ColorEditFixed(hashed_string.c_str(), v[0], v[1], v[2], v[3]);

	ImGui::PopStyleColor();

	UpdateWidgetsFadingValue(fading_value);

	if (m_check_change_value && !m_changed_value)
		m_changed_value = ret;

	return ret;
}

void CMenuGui::BeginCheckChangeValue()
{
	if (!m_check_change_value)
		m_check_change_value = true;
}

void CMenuGui::EndCheckChangeValue()
{
	if (m_check_change_value)
	{
		m_check_change_value = false;
		m_changed_value = false;
	}
}

bool CMenuGui::IsChangedValue()
{
	return m_changed_value;
}

float& CMenuGui::FindWidgetsFadingValue(std::string label)
{
	auto it = m_widgets_list.find(label);

	if (it == m_widgets_list.end())
	{
		m_widgets_list.insert({ label, 0.00f });
		it = m_widgets_list.find(label);
	}

	return it->second;
}

void CMenuGui::UpdateWidgetsFadingValue(float& fading_value)
{
	if (ImGui::IsItemHovered())
		fading_value = std::min(fading_value + GImGui->IO.DeltaTime * 6.f, 1.00f);
	else
		fading_value = std::max(fading_value - GImGui->IO.DeltaTime * 6.f, 0.00f);
}

ImColor fix_color(int z, int y, int x, int w)
{
	return ImColor(x, y, z, w);
}



//128, 34, 214
void CMenuThemes::SetDefaultDarkTheme()
{
	GImGui->Style.Colors[ImGuiCol_Text] = fix_color(255, 255, 255, 255);
	GImGui->Style.Colors[ImGuiCol_WindowBg] = fix_color(26, 24, 28, 255);
	GImGui->Style.Colors[ImGuiCol_PopupBg] = fix_color(41, 38, 43, 255);
	GImGui->Style.Colors[ImGuiCol_ChildBg] = fix_color(32, 30, 35, 255);
	GImGui->Style.Colors[ImGuiCol_FrameBg] = fix_color(61, 59, 63, 255);
	GImGui->Style.Colors[ImGuiCol_FrameBgHovered] = fix_color(96, 93, 96, 255);
	GImGui->Style.Colors[ImGuiCol_FrameBgActive] = fix_color(146, 36, 248, 255);
	GImGui->Style.Colors[ImGuiCol_CheckMark] = fix_color(146, 36, 248, 255);
	GImGui->Style.Colors[ImGuiCol_TitleBg] = fix_color(146, 36, 248, 150);
	GImGui->Style.Colors[ImGuiCol_TitleBgActive] = fix_color(146, 36, 248, 150);
	GImGui->Style.Colors[ImGuiCol_Tab] = fix_color(146, 36, 248, 150);
	GImGui->Style.Colors[ImGuiCol_TabHovered] = fix_color(146, 36, 248, 150);
	GImGui->Style.Colors[ImGuiCol_TabActive] = fix_color(146, 36, 248, 255);
	GImGui->Style.Colors[ImGuiCol_Button] = fix_color(61, 59, 63, 255);
	GImGui->Style.Colors[ImGuiCol_ButtonHovered] = fix_color(96, 93, 96, 255);
	GImGui->Style.Colors[ImGuiCol_ButtonActive] = fix_color(103, 100, 103, 255);
	GImGui->Style.Colors[ImGuiCol_Header] = fix_color(0, 0, 0, 0);
	GImGui->Style.Colors[ImGuiCol_HeaderHovered] = fix_color(61, 59, 63, 150);
	GImGui->Style.Colors[ImGuiCol_HeaderActive] = fix_color(61, 59, 63, 150);
	GImGui->Style.Colors[ImGuiCol_Border] = fix_color(41, 38, 43, 255);
	GImGui->Style.Colors[ImGuiCol_BorderShadow] = fix_color(18, 18, 35, 255);//ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	GImGui->Style.Colors[ImGuiCol_ScrollbarBg] = fix_color(0.37f * 255, 0.37f * 255, 0.37f * 255, 0);
	GImGui->Style.Colors[ImGuiCol_ScrollbarGrab] = fix_color(80, 80, 80, 204);
	GImGui->Style.Colors[ImGuiCol_ScrollbarGrabHovered] = fix_color(100, 100, 100, 204);
	GImGui->Style.Colors[ImGuiCol_ScrollbarGrabActive] = fix_color(100, 100, 100, 255);
	GImGui->Style.Colors[ImGuiCol_ModalWindowDarkening] = fix_color(0, 0, 0, 180);

	

}

void CreateTexture(LPDIRECT3DDEVICE9 pDevice, unsigned char* data, int size, ImageInfo* image_info, int x = 32, int y = 32)
{
	D3DXCreateTextureFromFileInMemoryEx(pDevice ,data, size, 1000, 1000, D3DUSAGE_DYNAMIC, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &image_info->data);
	image_info->size.x = x;
	image_info->size.y = y;
}


bool CMenu::InitTextures(LPDIRECT3DDEVICE9 pDevice)
{
	CreateTexture(pDevice, menu_title_bytes, sizeof(menu_title_bytes), &g_pImageList[MenuTitleBg], 800, 60);

	CreateTexture(pDevice, rage_icon_bytes, sizeof(rage_icon_bytes), &g_pImageList[TabRageIcon]);
	CreateTexture(pDevice, legit_icon_bytes, sizeof(legit_icon_bytes), &g_pImageList[TabLegitIcon]);
	CreateTexture(pDevice, visuals_icon_bytes, sizeof(visuals_icon_bytes), &g_pImageList[TabVisualsIcon]);
	CreateTexture(pDevice, kreedz_icon_bytes, sizeof(kreedz_icon_bytes), &g_pImageList[TabKreedzIcon]);
	CreateTexture(pDevice, misc_icon_bytes, sizeof(misc_icon_bytes), &g_pImageList[TabMiscIcon]);
	CreateTexture(pDevice, configs_icon_bytes, sizeof(configs_icon_bytes), &g_pImageList[TabConfigsIcon]);
	CreateTexture(pDevice, console_icon_bytes, sizeof(console_icon_bytes), &g_pImageList[TabConsoleIcon]);



	CreateTexture(pDevice, wpn_pistols_icon_bytes, sizeof(wpn_pistols_icon_bytes), &g_pImageList[WpnPistolsIcon], 50, 20);
	CreateTexture(pDevice, wpn_rifles_icon_bytes, sizeof(wpn_rifles_icon_bytes), &g_pImageList[WpnRiflesIcon], 50, 20);
	CreateTexture(pDevice, wpn_snipers_icon_bytes, sizeof(wpn_snipers_icon_bytes), &g_pImageList[WpnSnipersIcon], 50, 20);
	CreateTexture(pDevice, wpn_shotguns_icon_bytes, sizeof(wpn_shotguns_icon_bytes), &g_pImageList[WpnShotgunsIcon], 50, 20);
	CreateTexture(pDevice, wpn_smgs_icon_bytes, sizeof(wpn_smgs_icon_bytes), &g_pImageList[WpnSmgsIcon], 50, 20);


	CreateTexture(pDevice, weapon_ak47_bytes, sizeof(weapon_ak47_bytes), &g_pImageList[WPN_AK47]);
	CreateTexture(pDevice, weapon_aug_bytes, sizeof(weapon_aug_bytes), &g_pImageList[WPN_AUG]);
	CreateTexture(pDevice, weapon_awp_bytes, sizeof(weapon_awp_bytes), &g_pImageList[WPN_AWP]);
	CreateTexture(pDevice, weapon_c4_bytes, sizeof(weapon_c4_bytes), &g_pImageList[WPN_C4]);
	CreateTexture(pDevice, weapon_deagle_bytes, sizeof(weapon_deagle_bytes), &g_pImageList[WPN_DEAGLE]);
	CreateTexture(pDevice, weapon_elite_bytes, sizeof(weapon_elite_bytes), &g_pImageList[WPN_ELITE]);
	CreateTexture(pDevice, weapon_famas_bytes, sizeof(weapon_famas_bytes), &g_pImageList[WPN_FAMAS]);
	CreateTexture(pDevice, weapon_fiveseven_bytes, sizeof(weapon_fiveseven_bytes), &g_pImageList[WPN_FIVESEVEN]);
	CreateTexture(pDevice, weapon_flashbang_bytes, sizeof(weapon_flashbang_bytes), &g_pImageList[WPN_FLASHBANG]);
	CreateTexture(pDevice, weapon_g3sg1_bytes, sizeof(weapon_g3sg1_bytes), &g_pImageList[WPN_G3SG1]);
	CreateTexture(pDevice, weapon_galil_bytes, sizeof(weapon_galil_bytes), &g_pImageList[WPN_GALIL]);
	CreateTexture(pDevice, weapon_glock18_bytes, sizeof(weapon_glock18_bytes), &g_pImageList[WPN_GLOCK18]);
	CreateTexture(pDevice, weapon_hegrenade_bytes, sizeof(weapon_hegrenade_bytes), &g_pImageList[WPN_HEGRENADE]);
	CreateTexture(pDevice, weapon_knife_bytes, sizeof(weapon_knife_bytes), &g_pImageList[WPN_KNIFE]);
	CreateTexture(pDevice, weapon_m249_bytes, sizeof(weapon_m249_bytes), &g_pImageList[WPN_M249]);
	CreateTexture(pDevice, weapon_m4a1_bytes, sizeof(weapon_m4a1_bytes), &g_pImageList[WPN_M4A1]);
	CreateTexture(pDevice, weapon_m3_bytes, sizeof(weapon_m3_bytes), &g_pImageList[WPN_M3]);
	CreateTexture(pDevice, weapon_mac10_bytes, sizeof(weapon_mac10_bytes), &g_pImageList[WPN_MAC10]);
	CreateTexture(pDevice, weapon_mp5_bytes, sizeof(weapon_mp5_bytes), &g_pImageList[WPN_MP5N]);
	CreateTexture(pDevice, weapon_p228_bytes, sizeof(weapon_p228_bytes), &g_pImageList[WPN_P228]);
	CreateTexture(pDevice, weapon_p90_bytes, sizeof(weapon_p90_bytes), &g_pImageList[WPN_P90]);
	CreateTexture(pDevice, weapon_scout_bytes, sizeof(weapon_scout_bytes), &g_pImageList[WPN_SCOUT]);
	CreateTexture(pDevice, weapon_sg550_bytes, sizeof(weapon_sg550_bytes), &g_pImageList[WPN_SG550]);
	CreateTexture(pDevice, weapon_sg552_bytes, sizeof(weapon_sg552_bytes), &g_pImageList[WPN_SG552]);
	CreateTexture(pDevice, weapon_smokegrenade_bytes, sizeof(weapon_smokegrenade_bytes), &g_pImageList[WPN_SMOKEGRENADE]);
	CreateTexture(pDevice, weapon_tmp_bytes, sizeof(weapon_tmp_bytes), &g_pImageList[WPN_TMP]);
	CreateTexture(pDevice, weapon_ump45_bytes, sizeof(weapon_ump45_bytes), &g_pImageList[WPN_UMP45]);
	CreateTexture(pDevice, weapon_usp_bytes, sizeof(weapon_usp_bytes), &g_pImageList[WPN_USP]);
	CreateTexture(pDevice, weapon_xm1014_bytes, sizeof(weapon_xm1014_bytes), &g_pImageList[WPN_XM1014]);
	CreateTexture(pDevice, defuser_bytes, sizeof(defuser_bytes), &g_pImageList[DefuserIcon]);
	return true;
}



//final menu here


static char input_buf[64];
static const char* weapons_pistols[] = { "subsection", "glock18", "usp", "p228", "deagle", "elite", "fiveseven" };
static const char* weapons_submachineguns[] = { "subsection", "m249", "tmp", "p90", "mp5", "mac10", "ump45" };
static const char* weapons_rifles[] = { "subsection", "m4a1", "galil", "famas", "aug", "ak47", "sg552" };
static const char* weapons_shotguns[] = { "subsection", "xm1014", "m3" };
static const char* weapons_snipers[] = { "subsection", "awp", "scout", "g3sg1", "sg550" };
enum WeaponTablesList { PISTOL, SMG, RIFLE, SHOTGUN, SNIPER, MAX_WEPON_GROUPS };

void WeaponCombo(CMenuGui* m_pGui, int selected_weapon_group, int* selected_weapon)
{
	switch (selected_weapon_group)
	{
	case PISTOL:	m_pGui->Combo(selected_weapon, "##weapon_group", weapons_pistols, IM_ARRAYSIZE(weapons_pistols), "", true); break;
	case SMG:		m_pGui->Combo(selected_weapon, "##weapon_group", weapons_submachineguns, IM_ARRAYSIZE(weapons_submachineguns), "", true); break;
	case RIFLE:		m_pGui->Combo(selected_weapon, "##weapon_group", weapons_rifles, IM_ARRAYSIZE(weapons_rifles), "", true); break;
	case SHOTGUN:	m_pGui->Combo(selected_weapon, "##weapon_group", weapons_shotguns, IM_ARRAYSIZE(weapons_shotguns), "", true); break;
	case SNIPER:	m_pGui->Combo(selected_weapon, "##weapon_group", weapons_snipers, IM_ARRAYSIZE(weapons_snipers), "", true);
	}
}

void ChangeToCurrentWeapon(int* selected_weapon_group, int* selected_weapon)
{
	/*if (g_pGlobals->m_bIsInGame && g_Local->m_bIsConnected && g_Weapon->m_iWeaponID)
	{
		const auto weapon_name = Game::GetWeaponName(g_Weapon->m_iWeaponID);

		for (int i = 1; i < IM_ARRAYSIZE(weapons_pistols); i++)
		{
			if (!weapon_name.compare(weapons_pistols[i]))
			{
				*selected_weapon_group = PISTOL;
				*selected_weapon = i;
				break;
			}
		}

		for (int i = 1; i < IM_ARRAYSIZE(weapons_submachineguns); i++)
		{
			if (!weapon_name.compare(weapons_submachineguns[i]))
			{
				*selected_weapon_group = SMG;
				*selected_weapon = i;
				break;
			}
		}

		for (int i = 1; i < IM_ARRAYSIZE(weapons_rifles); i++)
		{
			if (!weapon_name.compare(weapons_rifles[i]))
			{
				*selected_weapon_group = RIFLE;
				*selected_weapon = i;
				break;
			}
		}

		for (int i = 1; i < IM_ARRAYSIZE(weapons_shotguns); i++)
		{
			if (!weapon_name.compare(weapons_shotguns[i]))
			{
				*selected_weapon_group = SHOTGUN;
				*selected_weapon = i;
				break;
			}
		}

		for (int i = 1; i < IM_ARRAYSIZE(weapons_snipers); i++)
		{
			if (!weapon_name.compare(weapons_snipers[i]))
			{
				*selected_weapon_group = SNIPER;
				*selected_weapon = i;
				break;
			}
		}
	}*/
}

void GetCurrentWeaponId(int selected_weapon_group, int selected_weapon, int* current_weapon_id)
{
	/*if (selected_weapon)
	{
		switch (selected_weapon_group)
		{
		case PISTOL:	*current_weapon_id = Game::GetWeaponIndex(weapons_pistols[selected_weapon]); break;
		case SMG:		*current_weapon_id = Game::GetWeaponIndex(weapons_submachineguns[selected_weapon]); break;
		case RIFLE:		*current_weapon_id = Game::GetWeaponIndex(weapons_rifles[selected_weapon]); break;
		case SHOTGUN:	*current_weapon_id = Game::GetWeaponIndex(weapons_shotguns[selected_weapon]); break;
		case SNIPER:	*current_weapon_id = Game::GetWeaponIndex(weapons_snipers[selected_weapon]);
		}
	}
	else
	{
		switch (selected_weapon_group)
		{
		case PISTOL:	*current_weapon_id = WEAPON_DEAGLE; break;
		case SMG:		*current_weapon_id = WEAPON_UMP45; break;
		case RIFLE:		*current_weapon_id = WEAPON_AK47; break;
		case SHOTGUN:	*current_weapon_id = WEAPON_XM1014; break;
		case SNIPER:	*current_weapon_id = WEAPON_AWP;
		}
	}*/
}

static void ChangeValuesWholeGroup(int selected_weapon_group, int current_weapon_id)
{
	/*switch (selected_weapon_group)
	{
	case PISTOL:
		for (int i = 1; i < IM_ARRAYSIZE(weapons_pistols); i++)
			cvars::weapons[Game::GetWeaponIndex(weapons_pistols[i])] = cvars::weapons[current_weapon_id];
		break;
	case SMG:
		for (int i = 1; i < IM_ARRAYSIZE(weapons_submachineguns); i++)
			cvars::weapons[Game::GetWeaponIndex(weapons_submachineguns[i])] = cvars::weapons[current_weapon_id];
		break;
	case RIFLE:
		for (int i = 1; i < IM_ARRAYSIZE(weapons_rifles); i++)
			cvars::weapons[Game::GetWeaponIndex(weapons_rifles[i])] = cvars::weapons[current_weapon_id];
		break;
	case SHOTGUN:
		for (int i = 1; i < IM_ARRAYSIZE(weapons_shotguns); i++)
			cvars::weapons[Game::GetWeaponIndex(weapons_shotguns[i])] = cvars::weapons[current_weapon_id];
		break;
	case SNIPER:
		for (int i = 1; i < IM_ARRAYSIZE(weapons_snipers); i++)
			cvars::weapons[Game::GetWeaponIndex(weapons_snipers[i])] = cvars::weapons[current_weapon_id];
	}*/
}

void CMenu::DialogSettingsSaveAs(char* buf, size_t size)
{
	
}

void CMenu::DialogSettingsRename(char* buf, size_t size)
{
	
}

void CMenu::DialogSettingsReset()
{
	
}

void CMenu::DialogSettingsRemove()
{
	
}

void CMenu::DialogFindAndReplace(char* buf)
{
	
}

static std::vector<TabWidgetsData> main_tables_data;
static std::vector<TabWidgetsData> weapon_tables_data;
static std::vector<TabWidgetsData> rage_tables_data;
static std::vector<TabWidgetsData> rage_anti_aim_tables_data;
static std::vector<TabWidgetsData> visuals_tables_data;
static std::vector<TabWidgetsData> visuals_other_tables_data;
static std::vector<TabWidgetsData> misc_tables_data;

static float timeToNextConfigRefresh = 0.1f;

void CMenu::Draw()
{
	enum MainTablesList { LEGIT, RAGE, VISUALS, KREEDZ, MISC, CONFIGS, CONSOLE };
	enum RageTablesList { RAGE_MAIN, RAGE_WEAPON };
	enum RageAntiAimTablesList { RAGE_ANTIAIM_MAIN, RAGE_ANTIAIM_STAND, RAGE_ANTIAIM_MOVE };
	enum VisualsTablesList { VISUALS_ESP, VISUALS_CHAMS, VISUALS_OTHER, VISUALS_GUI, VISUALS_COLORS };
	enum VisualsOtherTablesList { VISUALS_OTHER_LOCAL, VISUALS_OTHER_WORLD };
	enum MiscTablesList { MISC_GENERAL, MISC_ENHANCEMENT };



	







	if (main_tables_data.empty())
	{
		main_tables_data.push_back(TabWidgetsData{ "LEGIT", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "RAGE", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "VISUALS", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "INVENTORY", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "MISC", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "CONFIGS", 0.f });
		main_tables_data.push_back(TabWidgetsData{ "CONSOLE", 0.f });
	}

	if (weapon_tables_data.empty())
	{
		weapon_tables_data.push_back(TabWidgetsData{ "PISTOL", 0.f });
		weapon_tables_data.push_back(TabWidgetsData{ "SMG", 0.f });
		weapon_tables_data.push_back(TabWidgetsData{ "RIFLE", 0.f });
		weapon_tables_data.push_back(TabWidgetsData{ "SHOTGUN", 0.f });
		weapon_tables_data.push_back(TabWidgetsData{ "SNIPER", 0.f });
	}

	if (rage_tables_data.empty())
	{
		rage_tables_data.push_back(TabWidgetsData{ "MAIN", 0.f });
		rage_tables_data.push_back(TabWidgetsData{ "WEAPON", 0.f });
	}

	if (rage_anti_aim_tables_data.empty())
	{
		rage_anti_aim_tables_data.push_back(TabWidgetsData{ "MAIN", 0.f });
		rage_anti_aim_tables_data.push_back(TabWidgetsData{ "STAND", 0.f });
		rage_anti_aim_tables_data.push_back(TabWidgetsData{ "MOVE", 0.f });
	}

	if (visuals_tables_data.empty())
	{
		visuals_tables_data.push_back(TabWidgetsData{ "ESP", 0.f });
		visuals_tables_data.push_back(TabWidgetsData{ "CHAMS", 0.f });
		visuals_tables_data.push_back(TabWidgetsData{ "OTHER", 0.f });
		visuals_tables_data.push_back(TabWidgetsData{ "GUI", 0.f });
		visuals_tables_data.push_back(TabWidgetsData{ "COLORS", 0.f });
	}

	if (visuals_other_tables_data.empty())
	{
		visuals_other_tables_data.push_back(TabWidgetsData{ "LOCAL", 0.f });
		visuals_other_tables_data.push_back(TabWidgetsData{ "WORLD", 0.f });
	}

	if (misc_tables_data.empty())
	{
		misc_tables_data.push_back(TabWidgetsData{ "GENERAL", 0.f });
		misc_tables_data.push_back(TabWidgetsData{ "ENHANCEMENT", 0.f });
	}

	if (!m_bIsOpened)
		return;

	if (m_pGui->Begin("##menu", ImVec2(800, 600)))
	{
		PostProcessing::performFullscreenBlur(ImGui::GetWindowDrawList(), 1.f);
		m_WindowPos = GImGui->CurrentWindow->Pos;
		m_WindowSize = GImGui->CurrentWindow->Size;
		m_WindowCanvasPos = ImVec2(m_WindowPos.x, m_WindowPos.y + MENU_TAB_HEIGHT);
		m_WindowCanvasSize = ImVec2(m_WindowSize.x, m_WindowSize.y - MENU_TAB_HEIGHT - WINDOW_UNDERGROUND_HEIGHT);

		m_pGui->TabBackground();
		m_pGui->TabList(main_tables_data, m_iSelectedTab, m_iHoveredTab);

		ImGui::SetNextWindowPos(m_WindowCanvasPos);

		m_pGui->BeginCanvas("##menu_canvas", m_WindowCanvasSize);
		m_pGui->TabSeparator();

		ImGui::PushFont(g_pFontList[Verdana_13px]);

		ImVec2 child_size;

		switch (m_iSelectedTab)
		{
		case LEGIT:
		{
			static int weapon_tables_selected, weapon_tables_hovered;
			static int current_weapon_id, selected_weapon[MAX_WEPON_GROUPS];
			static bool auto_change_current_weapon;

			if (cvars::legitbot.active && cvars::ragebot.active)
				cvars::ragebot.active = false;

			ImGui::Spacing(WINDOW_PADDING_SPACING);
			ImGui::SameLine(WINDOW_PADDING_SAMELINE);

			ImGui::BeginGroup();

			m_pGui->SetChildSize(child_size);

			child_size.y = FEATURE_BUTTON_SIZE;

			m_pGui->SmallGroupBox("##visuals_general", child_size, [&]()
				{ m_pGui->Checkbox(&auto_change_current_weapon, "Current"); }, [&]()
				{ WeaponCombo(m_pGui, weapon_tables_selected, &selected_weapon[weapon_tables_selected]); });

			if (auto_change_current_weapon)
				ChangeToCurrentWeapon(&weapon_tables_selected, &selected_weapon[weapon_tables_selected]);

			GetCurrentWeaponId(weapon_tables_selected, selected_weapon[weapon_tables_selected], &current_weapon_id);

			m_pGui->BeginCheckChangeValue();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			child_size.x += child_size.x + WINDOW_PADDING_SAMELINE;

			m_pGui->BeginGroupBox("##LegitWeaponList", child_size);
			m_pGui->TabWeaponList(weapon_tables_data, weapon_tables_selected, weapon_tables_hovered);
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			ImGui::BeginGroup();

			m_pGui->SetChildSize(child_size);

			child_size.y -= WINDOW_PADDING_SAMELINE * 2.f;
			child_size.y *= 0.33f;

			m_pGui->BeginGroupBox("General", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->SetID("##legit_general");
			

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			const char* aim_recoil_standalone[] = { "None", "Default", "Return angles" };

			m_pGui->BeginGroupBox("Aimbot main", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->SetID("##legit_aimbot_main");
			

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			child_size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;

			m_pGui->BeginGroupBox("Triggerbot main", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->SetID("##legit_triggerbot_main");
			
			trigger_1();


			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::EndGroup();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			const char* aim_psilent_type[] = { "Manual", "Automatic fire" };
			const char* aim_psilent_triggers[] = { "Standing", "On land", "In air" };
			const char* aim_accuracy_boost[] = { "None", "Bound box (Recoil)", "Bound box (Recoil / Spread)", "Recoil", "Recoil / Spread" };
			const char* aim_hitboxes[] = { "Head", "Neck", "Chest", "Stomach", "Arms", "Legs" };

			m_pGui->SetChildSize(child_size);
			m_pGui->BeginGroupBox("Aimbot", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->SetID("##legit_aimbot");
			

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);

			const char* trigger_hitboxes[] = { "Head", "Neck", "Chest", "Stomach", "Arms", "Legs" };
			const char* trigger_accuracy_boost[] = { "None", "Recoil", "Recoil / Spread" };

			m_pGui->BeginGroupBox("Triggerbot", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->SetID("##legit_triggerbot");
			

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::EndGroup();

			if (!selected_weapon[weapon_tables_selected] && m_pGui->IsChangedValue())
				ChangeValuesWholeGroup(weapon_tables_selected, current_weapon_id);

			m_pGui->EndCheckChangeValue();

			break;
		}
		case RAGE:
		{
			static int rage_tables_selected, rage_tables_hovered;
			static int rage_anti_aim_tables_selected, rage_anti_aim_tables_hovered;

			if (cvars::ragebot.active && cvars::legitbot.active)
				cvars::legitbot.active = false;

			m_pGui->TabFeaturesList(rage_tables_data, rage_tables_selected, rage_tables_hovered);

			switch (rage_tables_selected)
			{
			case RAGE_MAIN:
			{
				ImGui::Spacing(WINDOW_PADDING_SPACING);
				ImGui::SameLine(WINDOW_PADDING_SAMELINE);

				const char* raim_type[] = { "Visible", "Silent (Client-Side)", "Perfect silent (Server-Side)" };
				const char* raim_auto_scope[] = { "None", "No unzoom", "Unzoom" };
				const char* raim_remove_spread[] = { "None", "Pitch / Yaw", "Pitch / Roll", "Pitch / Yaw / Roll" };
				const char* raim_resolver_pitch[] = { "None", "Breakpoint 90∞" };
				const char* raim_resolver_yaw[] = { "None", "Desyns bruteforce" };
				const char* raim_delayshot[] = { "Unlag", "History" };
				const char* raim_fps_mitigations[] = { "Traces only if can attack", "Don't trace arms points", "Don't trace legs points" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("General", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##rage_general");
				

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				child_size.y = 32.f;

				m_pGui->BeginGroupBox("##Anti-Aim", child_size);
				m_pGui->TabFeaturesList(rage_anti_aim_tables_data, rage_anti_aim_tables_selected, rage_anti_aim_tables_hovered);
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Anti-Aim", child_size);
				m_pGui->BeginWidgetsGroup();

				switch (rage_anti_aim_tables_selected)
				{
				case RAGE_ANTIAIM_MAIN:
				{
					const char* aa_roll[] = { "None", "Sideways 50∞", "Sideways 90∞", "Sideways 180∞", "Static" };
					const char* aa_conditions[] = { "On knife", "On grenades", "On freeze period" };
					const char* aa_at_targets[] = { "None", "Closest by FOV", "Average" };

					m_pGui->SetID("##rage_antiaim_main");
				

					break;
				}
				case RAGE_ANTIAIM_STAND:
				{
					const char* aa_side[] = { "Left", "Right" };
					const char* aa_stand_pitch[] = { "None", "Down", "Up", "Fake down", "Fake up", "Jitter", "Fake jitter" };
					const char* aa_stand_yaw[] = { "None", "Backwards", "Sideways 90∞", "Sideways 140∞", "Static", "Local view", "Backwards desyns", };
					const char* aa_stand_desync[] = { "None", "Default", "Max delta" };

					m_pGui->SetID("##rage_antiaim_stand");
					

					break;
				}
				case RAGE_ANTIAIM_MOVE:
				{
					const char* aa_move_pitch[] = { "None", "Down", "Up", "Fake down", "Fake up", "Jitter", "Fake jitter" };
					const char* aa_move_yaw[] = { "None", "Backwards", "Local view", "Gait sideways 120∞" };

					m_pGui->SetID("##rage_antiaim_move");
					

				}
				}

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				const char* fakelag_triggers[] = { "In move", "In air" };
				const char* fakelag_type[] = { "Maximum", "Break lag compensation" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Fakelag", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##rage_fakelag");
				

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				break;
			}
			case RAGE_WEAPON:
			{
				static int weapon_tables_selected, weapon_tables_hovered;
				static int current_weapon_id, selected_weapon[MAX_WEPON_GROUPS];
				static bool auto_change_current_weapon;

				ImGui::Spacing(WINDOW_PADDING_SPACING);
				ImGui::SameLine(WINDOW_PADDING_SAMELINE);

				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y = FEATURE_BUTTON_SIZE;

				m_pGui->SmallGroupBox("##visuals_general", child_size, [&]()
					{ m_pGui->Checkbox(&auto_change_current_weapon, "Current"); }, [&]()
					{ WeaponCombo(m_pGui, weapon_tables_selected, &selected_weapon[weapon_tables_selected]); });

				if (auto_change_current_weapon)
					ChangeToCurrentWeapon(&weapon_tables_selected, &selected_weapon[weapon_tables_selected]);

				GetCurrentWeaponId(weapon_tables_selected, selected_weapon[weapon_tables_selected], &current_weapon_id);

				m_pGui->BeginCheckChangeValue();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				child_size.x += child_size.x + WINDOW_PADDING_SAMELINE;

				m_pGui->BeginGroupBox("##RageWeaponList", child_size);
				m_pGui->TabWeaponList(weapon_tables_data, weapon_tables_selected, weapon_tables_hovered);
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				const char* raim_target_selection[] = { "Highest damage", "Closest by FOV", "Hitbox weights" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Target", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##rage_weapon_target");
				

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				const char* raim_hitboxes[] = { "Head", "Neck", "Chest", "Stomach", "Arms", "Legs" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Aimbot", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##rage_weapon_aimbot");
				
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				const char* raim_autostop[] = { "None", "Minimal speed", "Full stop" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Accuracy", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##rage_weapon_accuracy");
			

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();

				if (!selected_weapon[weapon_tables_selected] && m_pGui->IsChangedValue())
					ChangeValuesWholeGroup(weapon_tables_selected, current_weapon_id);

				m_pGui->EndCheckChangeValue();

				break;
			}
			}

			m_pGui->TabShadow(GImGui->CurrentWindow->Pos + ImVec2(0, 36), GImGui->CurrentWindow->Pos + ImVec2(0, 36) +
				ImVec2(GImGui->CurrentWindow->Size.x, 20), ImVec4(0.08f, 0.08f, 0.08f, 1.00f));

			break;
		}
		case VISUALS:
		{
			static int visuals_tables_selected, visuals_tables_hovered;
			static int visuals_other_tables_selected, visuals_other_tables_hovered;

			m_pGui->TabFeaturesList(visuals_tables_data, visuals_tables_selected, visuals_tables_hovered);

			ImGui::Spacing(WINDOW_PADDING_SPACING);
			ImGui::SameLine(WINDOW_PADDING_SAMELINE);

			switch (visuals_tables_selected)
			{
			case VISUALS_ESP:
			{
				const char* player_filters[] = { "Local", "Enemies", "Teammates" };
				const char* player_filters_without_local[] = { "Enemies", "Teammates" };
				const char* player_box_types[] = { "None", "Default", "Corner", "Round" };
				const char* player_pos[] = { "None", "Left", "Right", "Top", "Bot" };
				const char* player_distance_measurement[] = { "Units", "Meters" };
				const char* player_hiboxes[] = { "None", "Only head", "All hitboxes" };
				const char* player_out_of_fov[] = { "Arrows", "Circles", "Rhombuses" };
				const char* player_out_of_fov_additional_info[] = { "Name", "Weapon", "Distance" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Player", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_players_player");
				

				StreamProofESP::aimw_g_1();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE;
				child_size.y *= 0.5f;

				m_pGui->BeginGroupBox("Weapons", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_players_globals");
				
				StreamProofESP::aimw_g_3();


				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->BeginGroupBox("Projectiles", child_size);
				m_pGui->BeginWidgetsGroup();
				
				m_pGui->SetID("##visuals_players_projectiles");
				StreamProofESP::aimw_g_4();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE * 2.f;
				child_size.y *= 0.33f;

				m_pGui->BeginGroupBox("Glow", child_size);
				m_pGui->BeginWidgetsGroup();
				Glow::drawgl();
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->BeginGroupBox("Thirdperson", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_players_tp");
				Visuals::g2();
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				child_size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;

				m_pGui->BeginGroupBox("Out of FOV", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_players_out_of_fov");
				
				Visuals::g3();


				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				break;
			}
			case VISUALS_CHAMS:
			{
				const char* player_filters[] = { "Local", "Enemies", "Teammates" };
				const char* player_filters_without_local[] = { "Enemies", "Teammates" };
				const char* colored_models[] = { "None", "Flat", "Darkened", "Ligthed", "Texture" };

				const char* colored_models_health_based[] = { "None", "Visible", "Always" };
				const char* origin[] = { "Legs", "Body", "Head" };

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Player", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_players");
			
				new_chams_1();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE;
				child_size.y *= 0.5f;

				m_pGui->BeginGroupBox("Local", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_globals");
				new_chams_2();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->BeginGroupBox("Backtrack", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_backtrack");
				
				new_chams_6();
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE * 2.f;
				child_size.y *= 0.33f;

				m_pGui->BeginGroupBox("Weapons", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_dlight");
				
				new_chams_3();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->BeginGroupBox("Hands", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_elight");
				new_chams_4();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				child_size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;

				m_pGui->BeginGroupBox("Sleeves", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_colored_models_hands");
				new_chams_5();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				break;
			}
			case VISUALS_OTHER:
			{
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE * 2.f;
				child_size.y *= 0.33f;

				m_pGui->BeginGroupBox("Main", child_size);
				m_pGui->BeginWidgetsGroup();
			

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				child_size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;

				m_pGui->BeginGroupBox("Crosshair", child_size);
				m_pGui->BeginWidgetsGroup();
				
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				child_size.y = 32.f;

				m_pGui->BeginGroupBox("##visuals_other_tabs", child_size);
				m_pGui->TabFeaturesList(visuals_other_tables_data, visuals_other_tables_selected, visuals_other_tables_hovered);
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->SetChildSize(child_size);

				switch (visuals_other_tables_selected)
				{
				case VISUALS_OTHER_LOCAL:
				{
					m_pGui->BeginGroupBox("Local", child_size);
					m_pGui->BeginWidgetsGroup();
					m_pGui->SetID("##visuals_other_local");
					Visuals::g5();

					break;
				}
				case VISUALS_OTHER_WORLD:
				{
					m_pGui->BeginGroupBox("World", child_size);
					m_pGui->BeginWidgetsGroup();
					m_pGui->SetID("##visuals_other_world");
					Visuals::g4();
				}
				}

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
				ImGui::BeginGroup();

				m_pGui->SetChildSize(child_size);

				child_size.y -= WINDOW_PADDING_SAMELINE;
				child_size.y *= 0.5f;

				m_pGui->BeginGroupBox("Removals", child_size);
				m_pGui->BeginWidgetsGroup();
				Visuals::g1();
				
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::Spacing(3);

				m_pGui->BeginGroupBox("Effects", child_size);
				m_pGui->BeginWidgetsGroup();
				m_pGui->SetID("##visuals_other_effects");
				

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::EndGroup();
				break;
			}
			case VISUALS_GUI:
			{

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("GUI", child_size);
				m_pGui->BeginWidgetsGroup();
				Misc::aimware_gui_1();
				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

			
				break;
			}
			case VISUALS_COLORS:
			{
				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Player", child_size);
				m_pGui->BeginWidgetsGroup();
				
				StreamProofESP::aimw_g_2();

				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Weapons", child_size);
				m_pGui->BeginWidgetsGroup();
				
				StreamProofESP::aimw_g_22();


				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();

				ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

				m_pGui->SetChildSize(child_size);
				m_pGui->BeginGroupBox("Projectiles", child_size);
				m_pGui->BeginWidgetsGroup();
				
				StreamProofESP::aimw_g_222();



				m_pGui->EndWidgetsGroup();
				m_pGui->EndGroupBox();
			}
			}

			m_pGui->TabShadow(GImGui->CurrentWindow->Pos + ImVec2(0, 36), GImGui->CurrentWindow->Pos + ImVec2(0, 36) +
				ImVec2(GImGui->CurrentWindow->Size.x, 20), ImVec4(0.08f, 0.08f, 0.08f, 1.00f));

			break;
		}
		case KREEDZ:
		{
			ImGui::Spacing(WINDOW_PADDING_SPACING);
			ImGui::SameLine(WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);

			ImVec2 button_size = ImVec2(child_size.x - WINDOW_WIDGETS_PADDING_SAMELINE * 2.f, 26);

			m_pGui->BeginGroupBox("Main", child_size);
			m_pGui->BeginWidgetsGroup();
			

			static bool isInAddMode = false;

			anothetr_exam(button_size, isInAddMode);



			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);
			m_pGui->BeginGroupBox("Inventory", child_size + ImVec2(child_size.x, 0));
			m_pGui->BeginWidgetsGroup();

			button_size = ImVec2(2 * child_size.x - WINDOW_WIDGETS_PADDING_SAMELINE * 2.f, 26);
			_1_another_exam(button_size, isInAddMode, child_size + ImVec2(child_size.x, 0));

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			

			break;
		}
		case MISC:
		{
			static int misc_tables_selected, misc_tables_hovered;

			//m_pGui->TabFeaturesList(misc_tables_data, misc_tables_selected, misc_tables_hovered);

			ImGui::Spacing(WINDOW_PADDING_SPACING);
			ImGui::SameLine(WINDOW_PADDING_SAMELINE);

			
			const char* kb_attack_type[] = { "Swing", "Stab" };
			const char* kb_aim_type[] = { "Disabled", "Visible", "Silent (Client-Side)", "Perfect silent (Server-Side)" };
			const char* kb_aim_hitbox[] = { "Head", "Neck", "Chest", "Stomach", "Arms", "Legs" };
			const char* kb_conditions[] = { "Don't shoot spectators", "Don't shoot in back", "Don't shoot in shield" };
			ImVec2 button_size = ImVec2(child_size.x - WINDOW_WIDGETS_PADDING_SAMELINE * 2.f, 26);
			m_pGui->SetChildSize(child_size);
			m_pGui->BeginGroupBox("Main", child_size);
			m_pGui->BeginWidgetsGroup();

			
			Misc::aimware_gui_2();
			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
			ImGui::BeginGroup();

			m_pGui->SetChildSize(child_size);

			child_size.y -= WINDOW_PADDING_SAMELINE;
			child_size.y *= 0.5f;

			m_pGui->BeginGroupBox("Additionale larita1", child_size);
			m_pGui->BeginWidgetsGroup();
		


			Misc::aimware_gui_4();



			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			m_pGui->BeginGroupBox("Additional larita2", child_size);
			m_pGui->BeginWidgetsGroup();


			const auto zwindow_width = ImGui::GetWindowWidth();
			const auto zmultiline_width = zwindow_width - ImGui::GetCursorPosX() - WINDOW_PADDING_SPACING;
			auto zbutton_width = (zmultiline_width);
			auto zbutton_height = 22.f;

			Misc::aimware_gui_5(child_size.x - 25, ImVec2(zbutton_width, zbutton_height));

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::EndGroup();
			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);
			ImGui::BeginGroup();

			m_pGui->SetChildSize(child_size);

			child_size.y -= WINDOW_PADDING_SAMELINE * 2.f;
			child_size.y *= 0.33f;

			m_pGui->BeginGroupBox("Additional larita3", child_size);
			m_pGui->BeginWidgetsGroup();
			


			Misc::aimware_gui_7();


			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			m_pGui->BeginGroupBox("Additional larita4", child_size);
			m_pGui->BeginWidgetsGroup();

			
			
			
			Misc::aimware_gui_6(child_size.x - 25, ImVec2(0, 0));


			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::Spacing(3);

			child_size.y = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_SAMELINE;

			m_pGui->BeginGroupBox("Other", child_size);
			m_pGui->BeginWidgetsGroup();



			const auto window_width = ImGui::GetWindowWidth();
			const auto multiline_width = window_width - ImGui::GetCursorPosX() - WINDOW_PADDING_SPACING;
			auto button_width = (multiline_width);
			auto button_height = 22.f;
			
			
			Misc::aimware_gui_3();
			if (ImGui::Button("Unload cheat from game", ImVec2(button_width, button_height)))
				hooks->uninstall();

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::EndGroup();
			/*	break;
			}
			}*/

			break;
		}
		case CONFIGS:
		{
			static int selected_settings;

			auto& configItems = config->getConfigs();
			static int currentConfig = -1;

			static std::u8string buffer;

			static bool incrementalLoad = false;
			
			
			
			timeToNextConfigRefresh -= ImGui::GetIO().DeltaTime;
			if (timeToNextConfigRefresh <= 0.0f) {
				config->listConfigs();
				if (const auto it = std::find(configItems.begin(), configItems.end(), buffer); it != configItems.end())
					currentConfig = std::distance(configItems.begin(), it);
				timeToNextConfigRefresh = 0.1f;
			}

			if (static_cast<std::size_t>(currentConfig) >= configItems.size())
				currentConfig = -1;

			ImGui::Spacing(WINDOW_PADDING_SPACING);
			ImGui::SameLine(WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);

			ImVec2 button_size = ImVec2(child_size.x - WINDOW_WIDGETS_PADDING_SAMELINE * 2.f, 26);

			m_pGui->BeginGroupBox("Configurations", child_size);
			m_pGui->BeginWidgetsGroup();
			m_pGui->Checkbox(&incrementalLoad, "Incremental Load");


			if (ImGui::ListBox("", &currentConfig, [](void* data, int idx, const char** out_text) {
				auto& vector = *static_cast<std::vector<std::u8string>*>(data);
				*out_text = (const char*)vector[idx].c_str();
				return true;
				}, &configItems, configItems.size(), 5) && currentConfig != -1)
				buffer = configItems[currentConfig];
				ImGui::PushItemWidth(button_size.x);
				ImGui::PushID(0);
				if (ImGui::InputTextWithHint("", "config name", &buffer, ImGuiInputTextFlags_EnterReturnsTrue)) {
					if (currentConfig != -1)
						config->rename(currentConfig, buffer);
				}
				ImGui::PopID();
				ImGui::PopItemWidth();
				ImGui::NextColumn();


			if (ImGui::Button("Open config folder##settings", button_size))
				config->openConfigDir();

			if (ImGui::Button("Create config##settings", button_size))
				config->add(buffer.c_str());
		
			if (ImGui::Button("Reset config##settings", button_size))
				ImGui::OpenPopup("Config to reset");


			//add in extern function
			//done!
			thats_what_i_say(currentConfig,incrementalLoad, configItems, buffer, button_size);

	
			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);
			m_pGui->BeginGroupBox("Lua Scripts", child_size);
			m_pGui->BeginWidgetsGroup();

			ImGui::Text("Soon..");

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();

			ImGui::SameLine(0, WINDOW_PADDING_SAMELINE);

			m_pGui->SetChildSize(child_size);
			m_pGui->BeginGroupBox("Miscellaneous", child_size);
			m_pGui->BeginWidgetsGroup();

			//if (ImGui::Button("Open settings folder##settings", button_size))
			//	ShellExecute(NULL, "open", g_pGlobals->m_sSettingsPath.c_str(), NULL, NULL, SW_RESTORE);

			//ImGui::Spacing();
			//
			//if (ImGui::Button("Unload Cheat##settings", button_size))
			//	g_pGlobals->m_bIsUnloadingLibrary = true;

			m_pGui->EndWidgetsGroup();
			m_pGui->EndGroupBox();
			break;
		}
		case CONSOLE:
		{
			
		}
		}

		ImGui::PopFont();

		m_pGui->TabShadow(GImGui->CurrentWindow->Pos + ImVec2(0, 4), GImGui->CurrentWindow->Pos + ImVec2(GImGui->CurrentWindow->Size.x, 20), GImGui->Style.Colors[ImGuiCol_BorderShadow]);
		m_pGui->EndCanvas();
		m_pGui->UnderBackground();
		m_pGui->UnderContents();
		m_pGui->End();
	}

	//static int hovered_tab;
	//static int selected_tab = LEGIT;

	//ImGui::ShowStyleEditor();

	//m_pFadeGlobal->Init();

	//if (!m_pFadeGlobal->Close() && !m_bIsOpened)
	//	return;

	//m_pFadeGlobal->Open();
	//m_pFadeGlobal->Apply();

	//m_pGui->Begin(ImVec2(900, 675));
	//m_pGui->TabBg(m_pFadeGlobal->GetGlobalAlpha());

	//const auto window_width = ImGui::GetWindowWidth();

	//ImGui::SameLine(window_width / 3.2f);
	//ImGui::PushFont(g_pFontList[Verdana_17px]);

	//if (m_pGui->TabList(TabLabels, IM_ARRAYSIZE(TabLabels), &selected_tab, &hovered_tab))
	//	m_pFadeWidgets->Init();

	//ImGui::PopFont();
	//ImGui::PushFont(g_pFontList[Verdana_13px]);

	//ImGui::PushStyleColor(ImGuiCol_ChildBg, GImGui->Style.Colors[ImGuiCol_WindowBg]);
	//ImGui::BeginChild("##widgets", ImVec2(0, ImGui::GetContentRegionAvail().y - 20));
	//ImGui::PopStyleColor();

	////ImGui::Spacing(WINDOW_PADDING_Y);

	//m_pFadeWidgets->Run();

	//switch (selected_tab)
	//{
	//case RAGE:
	//	DrawRage();
	//	break;
	//case LEGIT:
	//	DrawLegit();
	//	break;
	//case VISUALS:
	//	DrawVisuals();
	//	break;
	//case KREEDZ:
	//	break;
	//case MISC:
	//{
	//	ImGui::Spacing();

	//	const auto child_width = (window_width - WINDOW_PADDING_X * 3.f) / 2.f;

	//	ImGui::SameLine(WINDOW_PADDING_X);

	//	auto child_height = GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_X;

	//	m_pGui->BeginChild("Miscellaneous", ImVec2(child_width, child_height));
	//	m_pGui->SetID("##misc_miscellaneous");
	//	//m_pGui->PushCondition(g_pGlobals->m_bIsSDL2Hooked);
	//	//m_pGui->PopCondition();
	//	
	//	
	//	//m_pGui->PushTextColor(ImVec4(1.00f, 1.00f, 0.00f, GImGui->Style.Colors[ImGuiCol_Text].w));


	//	//m_pGui->PopCondition();
	//	//m_pGui->PushTextColor(ImVec4(1.00f, 1.00f, 0.00f, GImGui->Style.Colors[ImGuiCol_Text].w));
	//	
	//	//m_pGui->PopTextColor();
	//	
	//	m_pGui->EndChild();

	//	ImGui::SameLine(0, WINDOW_PADDING_X);

	//	child_height = (GImGui->CurrentWindow->Size.y - ImGui::GetCursorPosY() - WINDOW_PADDING_X * 2.f) / 1.5f; // change this

	//	ImGui::BeginGroup();

	//	const char* kb_attack_type[] = { "Swing", "Stab" };
	//	const char* kb_aim_type[] = { "Disabled", "Visible", "Silent", "Perfect silent" };
	//	const char* kb_aim_hitbox[] = { "All", "Head" };

	//	m_pGui->BeginChild("Knifebot", ImVec2(child_width, child_height));
	//	m_pGui->SetID("##misc_knifebot");
	//	m_pGui->Checkbox(&cvars::misc.kb_enabled, "Enabled");
	//	//m_pGui->PushCondition(cvars::misc.kb_enabled);
	//	//m_pGui->Key(&cvars::misc.kb_key, "Key", true);
	//	m_pGui->Checkbox(&cvars::misc.kb_friendly_fire, "Friendly fire");
	//	m_pGui->Slider(&cvars::misc.kb_fov, "Maximum FOV", 0.f, 180.f, "%.1f∞", 1.f);
	//	//m_pGui->PushCondition(cvars::misc.kb_fov > 0.f);
	//	m_pGui->Combo(&cvars::misc.kb_attack_type, "Attack type", kb_attack_type, IM_ARRAYSIZE(kb_attack_type));
	//	m_pGui->Combo(&cvars::misc.kb_aim_type, "Aim type", kb_aim_type, IM_ARRAYSIZE(kb_aim_type));
	//	//m_pGui->PushCondition(cvars::misc.kb_aim_type);
	//	m_pGui->Combo(&cvars::misc.kb_aim_hitbox, "Aim hitbox", kb_aim_hitbox, IM_ARRAYSIZE(kb_aim_hitbox));
	//	m_pGui->Slider(&cvars::misc.kb_aim_hitbox_scale, "Aim hitbox scale", 1.f, 100.f, "%.0f%%", 1.f);
	//	//m_pGui->PopCondition();
	//	m_pGui->Slider(&cvars::misc.kb_swing_distance, "Swing distance", 16.f, 64.f, "%.1f units", 1.f);
	//	m_pGui->Slider(&cvars::misc.kb_stab_distance, "Stab distance", 16.f, 64.f, "%.1f units", 1.f);
	//	//m_pGui->PushTextColor(ImVec4(1.00f, 1.00f, 0.00f, GImGui->Style.Colors[ImGuiCol_Text].w));
	//	m_pGui->Checkbox(&cvars::misc.kb_position_adjustment, "Position adjustment", "ENG: Exploit allowing you to shoot at multiple positions of the target.\nRUS: Ёксплоит позвол€ющий стрел€ть в несколько позиций цели.");
	//	//m_pGui->PopTextColor();
	//	m_pGui->Checkbox(&cvars::misc.kb_dont_shoot_spectators, "Don't shoot spectators");
	//	m_pGui->Checkbox(&cvars::misc.kb_dont_shoot_in_back, "Don't shoot in back");
	//	m_pGui->Checkbox(&cvars::misc.kb_dont_shoot_in_shield, "Don't shoot in shield");
	//	//m_pGui->PopCondition(2);
	//	
	//	m_pGui->EndChild();

	//	ImGui::Spacing(WINDOW_PADDING_Y - 1);

	//	const auto multiline_width = window_width - ImGui::GetCursorPosX() - WINDOW_PADDING_X;

	//	auto button_width = (multiline_width);
	//	auto button_height = 22.f;

	//	if (ImGui::Button("Unload cheat from game", ImVec2(button_width, button_height)))
	//		g_pGlobals->m_bIsUnloadingLibrary = true;



	//	ImGui::EndGroup();

	//	break;
	//}
	//case CONFIGS:
	//{
	//	static char input_buf[64];

	//	m_pSettingsList->RefreshSettingsList();

	//	const auto item_width = Math::TranslateToEvenGreatest(window_width * 0.27f);
	//	const auto child_width = (item_width + GImGui->Style.ItemSpacing.x) * 2.f;
	//	const auto child_height = GImGui->CurrentWindow->Size.y - WINDOW_PADDING_X * 2.f - GImGui->Style.ItemSpacing.y - 15.f;

	//	ImGui::BeginChild("##group", ImVec2(child_width, child_height));
	//	ImGui::SameLine(WINDOW_PADDING_X);
	//	ImGui::SetNextItemWidth(item_width);

	//	if (m_pGui->ListBox("##settings", &m_pSettingsList->m_selected_settings, m_pSettingsList->m_settings_list, 13))
	//		update_contents = true;

	//	ImGui::SameLine();
	//	ImGui::BeginGroup();
	//	ImGui::SetNextItemWidth(item_width);
	//	
	//	if (ImGui::ListBox("##ini", &m_pSettingsList->m_selected_file, g_IniFile, IM_ARRAYSIZE(g_IniFile)))
	//		update_contents = true;

	//	auto button_width = (item_width - GImGui->Style.ItemSpacing.x) * 0.5f;
	//	auto button_height = 22.f;

	//	ImGui::Spacing();

	//	if (ImGui::Button("Load##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("CTRL + L"))
	//	{
	//		g_pSettings->Load(m_pSettingsList->GetFocusSettings());

	//		update_contents = true;
	//	}

	//	ImGui::SameLine();

	//	if (ImGui::Button("Save##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("CTRL + S"))
	//	{
	//		g_pSettings->Save(m_pSettingsList->GetFocusSettings());

	//		update_contents = true;
	//	}

	//	ImGui::Spacing();

	//	if (ImGui::Button("Reset##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("CTRL + ALT + R"))
	//		ImGui::OpenPopup("Reset##modal");

	//	ImGui::SameLine();

	//	if (ImGui::Button("Save as##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("CTRL + ALT + S"))
	//		ImGui::OpenPopup("Save as##modal");

	//	ImGui::Spacing();

	//	if (ImGui::Button("Remove##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("DELETE"))
	//	{
	//		if (m_pSettingsList->GetFocusSettings().compare("Default"))
	//			ImGui::OpenPopup("Remove##modal");
	//	}

	//	ImGui::SameLine();

	//	if (ImGui::Button("Rename##settings", ImVec2(button_width, button_height)) || m_pHotkeys->Is("CTRL + R"))
	//	{
	//		const auto& settings_name = m_pSettingsList->GetFocusSettings();

	//		if (settings_name.compare("Default"))
	//		{
	//			settings_name.copy(input_buf, sizeof(input_buf));
	//			ImGui::OpenPopup("Rename##modal");
	//		}
	//	}

	//	ImGui::Spacing();

	//	if (ImGui::Button("Open folder##settings", ImVec2(button_width, button_height - 1)) || m_pHotkeys->Is("CTRL + ALT + O"))
	//	{
	//		const auto path = g_pGlobals->m_sSettingsPath + m_pSettingsList->GetFocusSettings();
	//		ShellExecute(NULL, "open", path.c_str(), NULL, NULL, SW_RESTORE);
	//	}

	//	ImGui::SameLine();

	//	if (ImGui::Button("Open file##settings", ImVec2(button_width, button_height - 1)) || m_pHotkeys->Is("CTRL + ALT + F"))
	//	{
	//		const auto path = g_pGlobals->m_sSettingsPath + m_pSettingsList->GetFocusSettings() + g_IniFile[m_pSettingsList->m_selected_file];
	//		ShellExecute(NULL, "open", path.c_str(), NULL, NULL, SW_RESTORE);
	//	}

	//	ImGui::EndGroup();
	//	
	//	const auto popup_modal_size_with_input = ImVec2(250, 78);
	//	const auto popup_modal_size_without_input = ImVec2(250, 62);

	//	if (m_pPopupModal->Begin("Save as##modal", popup_modal_size_with_input))
	//	{
	//		DialogSettingsSaveAs(input_buf, sizeof(input_buf));
	//		m_pPopupModal->End();
	//	}

	//	if (m_pPopupModal->Begin("Rename##modal", popup_modal_size_with_input))
	//	{
	//		DialogSettingsRename(input_buf, sizeof(input_buf));
	//		m_pPopupModal->End();
	//	}

	//	if (m_pPopupModal->Begin("Remove##modal", popup_modal_size_without_input))
	//	{
	//		DialogSettingsRemove();
	//		m_pPopupModal->End();
	//	}

	//	if (m_pPopupModal->Begin("Reset##modal", popup_modal_size_without_input))
	//	{
	//		DialogSettingsReset();
	//		m_pPopupModal->End();
	//	}

	//	ImGui::Spacing(WINDOW_PADDING_Y);
	//	ImGui::SameLine(WINDOW_PADDING_X);

	//	const auto child_size = ImVec2(child_width - WINDOW_PADDING_X - 1, child_height - ImGui::GetCursorPosY() - 1);

	//	m_pGui->BeginChild("Other", child_size);

	//	if (ImGui::TreeNode("Information"))
	//	{
	//		ImGui::TextDisabled("[CTRL + L] - Load settings.");
	//		ImGui::TextDisabled("[CTRL + S] - Save settings.");
	//		ImGui::TextDisabled("[CTRL + ALT + R] - Reset settings.");
	//		ImGui::TextDisabled("[CTRL + ALT + S] - Save settings as.");
	//		ImGui::TextDisabled("[DELETE] - Remove settings.");
	//		ImGui::TextDisabled("[CTRL + R] - Rename settings.");
	//		ImGui::TextDisabled("[CTRL + ALT + O] - Open selected settings.");
	//		ImGui::TextDisabled("[CTRL + ALT + F] - Open selected file.");
	//		ImGui::TreePop();
	//	}

	//	m_pGui->EndChild();

	//	ImGui::EndChild();

	//	ImGui::SameLine();

	//	ImGui::BeginGroup();

	//	const auto multiline_width = window_width - ImGui::GetCursorPosX() - WINDOW_PADDING_X;
	//	const auto multiline_height = child_height - button_height - GImGui->Style.ItemSpacing.y * 2.f;

	//	static char buf[104448];

	//	if (update_contents)
	//	{
	//		memset(buf, 0, sizeof(buf));

	//		const auto path = g_pGlobals->m_sSettingsPath + m_pSettingsList->GetFocusSettings() + g_IniFile[m_pSettingsList->m_selected_file];

	//		if (Utils::FileExists(path))
	//			ReadFromFile(path, buf);

	//		update_contents = false;
	//	}

	//	ImGui::PushFont(g_pFontList[ProggyClean_13px]);
	//	ImGui::InputTextMultiline("##сontents", buf, sizeof(buf), ImVec2(multiline_width, multiline_height), ImGuiInputTextFlags_AllowTabInput);
	//	ImGui::PopFont();

	//	ImGui::Spacing();

	//	button_width = (multiline_width - GImGui->Style.ItemSpacing.x) * 0.5f;

	//	if (ImGui::Button("Find & replace", ImVec2(button_width, button_height)))
	//		ImGui::OpenPopup("Replace##modal");

	//	ImGui::SameLine();

	//	if (ImGui::Button("Apply changes", ImVec2(button_width, button_height)))
	//	{
	//		const auto path = g_pGlobals->m_sSettingsPath + m_pSettingsList->GetFocusSettings() + g_IniFile[m_pSettingsList->m_selected_file];

	//		std::ofstream out;
	//		out.open(path.c_str());

	//		if (out.is_open())
	//		{
	//			out << buf;
	//			out.close();
	//		}
	//	}

	//	ImGui::EndGroup();

	//	if (m_pPopupModal->Begin("Replace##modal", popup_modal_size_with_input))
	//	{
	//		DialogFindAndReplace(buf);
	//		m_pPopupModal->End();
	//	}

	//	ImGui::Spacing(2);
	//	ImGui::SameLine(WINDOW_PADDING_X);

	//	const auto flags = ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll;

	//	ImGui::SetNextItemWidth(Math::TranslateToEvenGreatest(window_width * 0.8925f));
	//	ImGui::InputText("##path", g_pGlobals->m_sSettingsPath.data(), g_pGlobals->m_sSettingsPath.size() + 1, flags);

	//	ImGui::SameLine();

	//	if (ImGui::Button("Open##settings", ImVec2(window_width - ImGui::GetCursorPosX() - WINDOW_PADDING_X, 15)))
	//		ShellExecute(NULL, "open", g_pGlobals->m_sSettingsPath.c_str(), NULL, NULL, SW_RESTORE); 

	//	break;
	//}
	//}

	//ImColor border_col_low_alpha = ImVec4(0.00f, 0.00f, 0.00f, 0.25f);
	//ImColor border_col_no_alpha = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	//GImGui->CurrentWindow->DrawList->AddRectFilledMultiColor(GImGui->CurrentWindow->Pos, GImGui->CurrentWindow->Pos +
	//	ImVec2(GImGui->CurrentWindow->Size.x, 15), border_col_low_alpha, border_col_low_alpha, border_col_no_alpha, border_col_no_alpha);

	//GImGui->Style.ItemSpacing = ImVec2(0, 1);

	//ImGui::EndChild();

	//m_pFadeWidgets->Reset();

	//ImGui::PushStyleColor(ImGuiCol_ChildBg, GImGui->Style.Colors[ImGuiCol_Button]);
	//ImGui::BeginChild("##information");
	//ImGui::PopStyleColor();

	//ImGui::Spacing(WINDOW_PADDING_Y);

	//GImGui->Style.ItemSpacing = ImVec2(8, 4);
	//
	//ImGui::SameLine(WINDOW_PADDING_X * 0.5f);

	//std::string info = "V6 for Counter-Strike 1.6 | Online: ";

	//if (!g_pGlobals->m_iOnlineNum)
	//{
	//	static auto instance = client_state->time;
	//	static auto count = 0;

	//	if (client_state->time > instance + 0.5)
	//	{
	//		for (int i = 0; i < count; i++)
	//			info.append(".");

	//		if (++count > 3)
	//			count = 0;
	//	}
	//}
	//else
	//	info.append(std::to_string(g_pGlobals->m_iOnlineNum));

	//ImGui::Text(info.c_str());

	//const std::string url = "https://hpp.ovh/";
	//const auto text_size = GImGui->Font->CalcTextSizeA(GImGui->Font->FontSize, FLT_MAX, 0, url.c_str());
	//
	//ImGui::SameLine(window_width - text_size.x - WINDOW_PADDING_X * 0.5f);
	//
	//m_pGui->Link(url);
	//	
	//ImGui::EndChild();
	//ImGui::PopFont();

	//m_pGui->End();

	//m_pFadeGlobal->Reset();
}






void CMenu::BeginScene()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4());
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	ImGui::SetNextWindowPos(ImVec2(), ImGuiCond_Always);
	ImGui::SetNextWindowSize(GImGui->IO.DisplaySize, ImGuiCond_Always);

	ImGui::Begin("##renderscene", nullptr, ImVec2(), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing);

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}



void CMenu::EndScene()
{
	GImGui->CurrentWindow->DrawList->PushClipRectFullScreen();

	ImGui::End();
}