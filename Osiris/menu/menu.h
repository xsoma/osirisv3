#pragma once
#include <Windows.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#include <string>
#include <functional>
#include <map>
#include <d3dx9.h>

#define ITEM_WIDTH_WITH_COLOR	-1.f
#define ITEM_WIDTH_WITH_COLOR2	-2.f

constexpr auto MENU_TAB_HEIGHT = 52.f;
constexpr auto WINDOW_PADDING_SAMELINE = 15.f;
constexpr auto WINDOW_PADDING_SPACING = 5;
constexpr auto WINDOW_WIDGETS_PADDING_SAMELINE = 17.f;
constexpr auto WINDOW_WIDGETS_PADDING_SPACING = 6;
constexpr auto WINDOW_UNDERGROUND_HEIGHT = 18.f;
constexpr auto FEATURE_BUTTON_SIZE = 32.f;

struct LinkData
{
	std::string url;
	bool hovered;
	bool clicked;
};

struct TabWidgetsData
{
	std::string label;
	float fading_value;
};

class CMenuPopupModal
{
public:
	bool Begin(std::string name, const ImVec2& size);
	void End();

	void Input(std::string name, char* buf, size_t buf_size);
	void Message(std::string message);
	bool Button(std::string name);

private:
	float GetItemWidth();
};

class KeyBind;
class CMenuGui
{
public:
	bool Begin(std::string name, const ImVec2& size);
	void BeginCanvas(std::string name, const ImVec2& size, bool border = false);
	void BeginGroupBox(std::string name, const ImVec2& size, bool border = true);
	void BeginWidgetsGroup();

	void End();
	void EndCanvas();
	void EndGroupBox();
	void EndWidgetsGroup();

	void SmallGroupBox(std::string name, const ImVec2& size, std::function<void()> widget_first, std::function<void()> widget_second);

	void UnderBackground();
	void UnderContents();

	void TabBackground();
	bool TabList(std::vector<TabWidgetsData>& data, int& selected, int& hovered);
	bool TabFeaturesList(std::vector<TabWidgetsData>& data, int& selected, int& hovered);
	bool TabWeaponList(std::vector<TabWidgetsData>& data, int& selected, int& hovered);
	void TabSeparator();
	void TabShadow(const ImVec2& pos, const ImVec2& size, const ImVec4& color);

	void SetID(const char* str_id);
	void SetChildSize(ImVec2& size);

	void Text(const char* fmt, ...);
	bool Checkbox(bool* v, std::string label, std::string message = "");
	bool Combo(int* v, std::string label, const char* items[], int size, std::string message = "", bool owned = false);
	bool MultiCombo(bool* v, std::string label, const char* items[], int size, std::string message = "");
	bool Slider(float* v, std::string label, float min, float max, const char* format, float power, std::string message = "");
	bool Slider(int* v, std::string label, int min, int max, const char* format, std::string message = "");
	bool ListBox(const char* label, int* current_item, std::vector<std::string>& values, int height_in_items);
	void Separator();
	void Link(std::string url);
	bool Key(void* v, std::string label, bool owned = false);
	bool KeyToggle(KeyBind* v, std::string label, bool owned);
	bool KeyToggle(void* v, std::string label, bool owned = false);
	bool KeyPress(void* v, std::string label, bool owned = false);
	bool ColorEdit(float* v, std::string label);

	void BeginCheckChangeValue();
	void EndCheckChangeValue();

	bool IsChangedValue();

private:
	std::map<std::string, float> m_widgets_list;

	std::string m_id;
	std::string m_message;

	bool m_check_change_value;
	bool m_changed_value;

	//std::unique_ptr<CMenuPopupModal> m_pPopupModal;

	float& FindWidgetsFadingValue(std::string label);
	void UpdateWidgetsFadingValue(float& fading_value);
};



namespace ImGui
{
	IMGUI_API bool ImageButtonTab(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));    // <0 frame_padding uses default frame padding settings. 0 for no padding
	IMGUI_API bool ImageButtonBySize(ImTextureID user_texture_id, const ImVec2& size, const ImVec2 image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0));    // <0 frame_padding uses default frame padding settings. 0 for no padding	
	IMGUI_API bool BeginCustom(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
	IMGUI_API bool BeginChildCustom(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
	IMGUI_API void EndChildCustom();
	IMGUI_API void Separator(float width);
}

typedef unsigned int FontFlags_t;
enum FontFlagList
{
	FontFlags_None = 1 << 0,
	FontFlags_Shadow = 1 << 1,
	FontFlags_Outline = 1 << 2,
	FontFlags_CenterX = 1 << 3,
	FontFlags_CenterY = 1 << 4,
};

class CDrawList
{
public:
	void AddLine(const ImVec2& a, const ImVec2& b, const ImColor& col);
	
	void AddRect(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false, float rounding = 0.f, int rounding_corners_flags = ImDrawCornerFlags_All, float thickness = 1.f);
	void AddRectCorner(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false);
	void AddRectFilled(const ImVec2& a, const ImVec2& b, const ImColor& col, float rounding = 0.f, int rounding_corners_flags = ImDrawCornerFlags_All);
	void AddRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left);
	void AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col, float thickness = 1.f);
	void AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col);
	void AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col, float thickness = 1.f);
	void AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col);
	void AddCircle(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12, float thickness = 1.f);
	void AddCircleFilled(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12);
	void AddText(const ImVec2& pos, const ImColor& col, FontFlags_t flags, const char* fmt, ...);
	void AddTextWrapped(const ImVec2& pos, const ImColor& col, float wrap_width, FontFlags_t flags, const char* fmt, ...);
	void AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a = ImVec2(), const ImVec2& uv_b = ImVec2(1, 1), const ImColor& col = ImColor(IM_COL32_WHITE));

	void PushLine(const ImVec2& a, const ImVec2& b, const ImColor& col);
	void PushRect(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false, float rounding = 0.f, int rounding_corners_flags = ImDrawCornerFlags_All, float thickness = 1.f);
	void PushRectCorner(const ImVec2& a, const ImVec2& b, const ImColor& col, bool outline = false);
	void PushRectFilled(const ImVec2& a, const ImVec2& b, const ImColor& col, float rounding = 0.f, int rounding_corners_flags = ImDrawCornerFlags_All);
	void PushRectFilledMultiColor(const ImVec2& a, const ImVec2& c, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left);
	void PushQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col, float thickness = 1.f);
	void PushQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImColor& col);
	void PushTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col, float thickness = 1.f);
	void PushTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImColor& col);
	void PushCircle(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12, float thickness = 1.f);
	void PushCircleFilled(const ImVec2& centre, float radius, const ImColor& col, int num_segments = 12);
	void PushText(const ImVec2& pos, const ImColor& col, FontFlags_t flags, const char* fmt, ...);
	void PushTextWrapped(const ImVec2& pos, const ImColor& col, float wrap_width, FontFlags_t flags, const char* fmt, ...);
	void PushImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a = ImVec2(), const ImVec2& uv_b = ImVec2(1, 1), const ImColor& col = ImColor(IM_COL32_WHITE));
};


inline CDrawList* DrawList = new CDrawList();



enum EFontList
{
	ProggyClean_13px,
	Verdana_1px,
	Verdana_2px,
	Verdana_3px,
	Verdana_4px,
	Verdana_5px,
	Verdana_6px,
	Verdana_7px,
	Verdana_8px,
	Verdana_9px,
	Verdana_10px,
	Verdana_11px,
	Verdana_12px,
	Verdana_13px,
	Verdana_14px,
	Verdana_15px,
	Verdana_16px,
	Verdana_17px,
	Verdana_18px,
	Verdana_19px,
	Verdana_20px,
	Verdana_21px,
	Verdana_22px,
	Verdana_23px,
	Verdana_24px,
	Verdana_25px,
	MAX_FONTS
};

enum EFontOffsetList
{
	FontProggyCleanOffset = 0,
	FontVerdanaOffset = 1
};

enum EImageList
{
	MenuTitleBg,

	TabRageIcon,
	TabLegitIcon,
	TabVisualsIcon,
	TabKreedzIcon,
	TabMiscIcon,
	TabConfigsIcon,
	TabConsoleIcon,

	WpnPistolsIcon,
	WpnSmgsIcon,
	WpnRiflesIcon,
	WpnShotgunsIcon,
	WpnSnipersIcon,

	WPN_NONE,
	WPN_P228,
	WPN_GLOCK,
	WPN_SCOUT,
	WPN_HEGRENADE,
	WPN_XM1014,
	WPN_C4,
	WPN_MAC10,
	WPN_AUG,
	WPN_SMOKEGRENADE,
	WPN_ELITE,
	WPN_FIVESEVEN,
	WPN_UMP45,
	WPN_SG550,
	WPN_GALIL,
	WPN_FAMAS,
	WPN_USP,
	WPN_GLOCK18,
	WPN_AWP,
	WPN_MP5N,
	WPN_M249,
	WPN_M3,
	WPN_M4A1,
	WPN_TMP,
	WPN_G3SG1,
	WPN_FLASHBANG,
	WPN_DEAGLE,
	WPN_SG552,
	WPN_AK47,
	WPN_KNIFE,
	WPN_P90,

	DefuserIcon,

	MAX_IMAGES
};

enum EImageOffsetsList
{
	IconsTabsOffset = 1,
	IconsWpnsOffset = 8,
	IconsEspWpnsOffset = 13
};

struct ImageInfo
{
	IDirect3DTexture9* data;
	ImVec2 size;
};

extern ImFont* g_pFontList[MAX_FONTS];
extern ImageInfo g_pImageList[MAX_IMAGES];


class CMenuThemes
{
public:
	void SetDefaultDarkTheme();
};


class CMenu
{
public:
	bool IsOpened();
	bool InitTextures(LPDIRECT3DDEVICE9 pDevice);
	void Open();
	void Close();
	void Toggle();

	void CursorState();
	void DrawFadeBg();
	void Draw();

	void BeginScene();

	void EndScene();

//private:
	inline static CMenuGui* m_pGui = new CMenuGui();
	//std::unique_ptr<CMenuPopupModal> m_pPopupModal;
	//std::unique_ptr<CMenuHotkeys> m_pHotkeys;
	//std::unique_ptr<CMenuSettingsList> m_pSettingsList;
	//std::unique_ptr<CMenuFadeBg> m_pFadeBg;
	inline static CMenuThemes* m_pThemes = new CMenuThemes();

	bool m_bIsOpened;

	ImVec2 m_WindowPos;
	ImVec2 m_WindowSize;
	ImVec2 m_WindowCanvasPos;
	ImVec2 m_WindowCanvasSize;

	int m_iSelectedTab;
	int m_iHoveredTab;

	void DialogSettingsSaveAs(char* buf, size_t size);
	void DialogSettingsRename(char* buf, size_t size);
	void DialogSettingsReset();
	void DialogSettingsRemove();
	void DialogFindAndReplace(char* buf);

	void DrawRage();
	void DrawLegit();
	void DrawVisuals();
};

inline static CMenu* g_pMenu = new CMenu();








struct bind_t
{
	int		keynum;
	int		type;
};

struct cvars_ragebot
{
	bool	active;
	bool	friendly_fire;
	bool	raim_delayshot[2];
	bool	raim_tapping_mode;
	bool	raim_auto_fire;
	int		raim_auto_scope;
	bool	raim_remove_recoil;
	int		raim_remove_spread;
	int		raim_type;
	float	raim_fov;
	bool	raim_low_fps_mitigations[3];
	float	raim_low_fps_value;
	int		raim_resolver_pitch;
	int		raim_resolver_yaw;
	bind_t	raim_force_body_key;
	bool	raim_target_selection[3];
	int		raim_target_weight_damage;
	int		raim_target_weight_fov;
	int		raim_target_weight_head;
	int		raim_target_weight_neck;
	int		raim_target_weight_chest;
	int		raim_target_weight_stomach;
	int		raim_target_weight_arms;
	int		raim_target_weight_legs;

	bool	aa_enabled;
	bool	aa_teammates;
	int		aa_at_targets;
	int		aa_stand_pitch;
	int		aa_stand_yaw;
	int		aa_stand_desync;
	bool	aa_stand_desync_helper;
	int		aa_side;
	bind_t	aa_side_key;
	bool	aa_side_switch_when_take_damage;
	int		aa_move_pitch;
	int		aa_move_yaw;
	int		aa_roll;
	float	aa_stand_yaw_static;
	float	aa_roll_static;
	bool	aa_untrusted_checks;
	bool	aa_conditions[3];

	bool	fakelag_enabled;
	bool	fakelag_while_shooting;
	bool	fakelag_on_enemy_in_pvs;
	bool	fakelag_on_peek;
	bool	fakelag_triggers[2];
	int		fakelag_type;
	int		fakelag_choke_limit;
};

struct cvars_legitbot
{
	bool	active;
	bool	friendly_fire;
	bool	position_adjustment;
	bool	desync_helper;
	int		target_switch_delay;
	bool	aim_auto_scope;
	bool	aim_smooth_independence_fps;
	int		aim_block_attack_after_kill;
	bool	aim_dont_shoot_in_shield;
	bool	aim_demochecker_bypass;
	int		aim_recoil_standalone;
	bind_t	aim_key;
	bind_t	aim_psilent_key;
	bool	trigger_only_scoped;
	bool	trigger_accurate_traces;
	float	trigger_hitbox_scale;
	bind_t	trigger_key;
};

struct cvars_weapons
{
	bool	aim_enabled;
	bool	aim_hitboxes[6];
	bool	aim_auto_fire;
	bool	aim_auto_penetration;
	int		aim_auto_penetration_min_damage;
	bool	aim_psilent_tapping_mode;
	float	aim_psilent_angle;
	float	aim_fov;
	float	aim_smooth_auto;
	float	aim_smooth_in_attack;
	float	aim_smooth_scale_fov;
	float	aim_recoil_smooth;
	float	aim_recoil_fov;
	int		aim_recoil_start;
	float	aim_recoil_pitch;
	float	aim_recoil_yaw;
	int		aim_maximum_lock_on_time;
	int		aim_delay_before_aiming;
	int		aim_delay_before_firing;
	bool	aim_psilent_triggers[3];
	int		aim_psilent_type;
	int		aim_accuracy_boost;
	bool	trigger_enabled;
	bool	trigger_auto_penetration;
	int		trigger_auto_penetration_min_damage;
	bool	trigger_hitboxes[6];
	int		trigger_accuracy_boost;

	bool	raim_enabled;
	bool	raim_hitboxes[6];
	bool	raim_auto_penetration;
	int		raim_auto_penetration_min_damage;
	float	raim_head_scale;
	float	raim_neck_scale;
	float	raim_chest_scale;
	float	raim_stomach_scale;
	float	raim_arms_scale;
	float	raim_legs_scale;
	int		raim_autostop;
	bool	raim_autostop_crouch;
};

struct cvars_visuals
{
	bool	active;
	bind_t	panic_key;
	bool	copyright;
	float	copyright_position[3];
	bool	antiscreen;
	bool	streamer_mode;

	float	esp_dormant_time;
	bool	esp_dormant_fadeout;
	bool	esp_dormant_update_by_sound;
	bool	esp_interpolate_history;
	int		esp_font_size;
	bool	esp_player;
	bool	esp_player_players[3];
	int 	esp_player_box;
	bool	esp_player_box_outline;
	int		esp_player_box_filled;
	float	esp_player_box_color_t[4];
	float	esp_player_box_color_ct[4];
	int		esp_player_health;
	bool	esp_player_health_percentage;
	float	esp_player_health_percentage_color[4];
	int		esp_player_armor;
	float	esp_player_armor_color[4];
	int		esp_player_name;
	float	esp_player_name_color[4];
	int		esp_player_weapon_text;
	float	esp_player_weapon_text_color[4];
	int		esp_player_weapon_icon;
	float	esp_player_weapon_icon_color[4];
	int		esp_player_money;
	float	esp_player_money_color[4];
	int		esp_player_distance;
	int		esp_player_distance_measurement;
	float	esp_player_distance_color[4];
	int		esp_player_actions;
	float	esp_player_actions_color[4];
	bool	esp_player_actions_bar;
	float	esp_player_actions_bar_color[4];
	int		esp_player_has_c4;
	float	esp_player_has_c4_color[4];
	int		esp_player_has_defusal_kits;
	float	esp_player_has_defusal_kits_color[4];
	float	esp_player_line_of_sight;
	float	esp_player_line_of_sight_color[4];
	int		esp_player_hitboxes;
	float	esp_player_hitboxes_color[4];
	bool	esp_player_hitboxes_hit_position;
	float	esp_player_hitboxes_hit_position_time;
	float	esp_player_hitboxes_hit_position_color[4];
	float	esp_player_hitboxes_hit_position_color2[4];
	bool	esp_player_skeleton;
	float	esp_player_skeleton_color[4];
	bool	esp_player_skeleton_backtrack;
	float	esp_player_skeleton_backtrack_color[4];
	bool	esp_player_glow;
	bool	esp_player_glow_players[3];
	int		esp_player_glow_amount;
	bool	esp_player_glow_color_health_based;
	float	esp_player_glow_color_t[4];
	float	esp_player_glow_color_ct[4];
	bool	esp_player_sounds;
	bool	esp_player_sounds_players[3];
	float	esp_player_sounds_time;
	float	esp_player_sounds_circle_radius;
	float	esp_player_sounds_color_t[4];
	float	esp_player_sounds_color_ct[4];
	bool	esp_player_out_of_fov;
	int		esp_player_out_of_fov_draw_type;
	bool	esp_player_out_of_fov_players[2];
	bool	esp_player_out_of_fov_additional_info[3];
	float	esp_player_out_of_fov_size;
	float	esp_player_out_of_fov_radius;
	bool	esp_player_out_of_fov_aspect_ratio;
	float	esp_player_out_of_fov_color_t[4];
	float	esp_player_out_of_fov_color_ct[4];
	bool	esp_player_out_of_fov_impulse_alpha;
	bool	esp_player_out_of_fov_outline;

	float	colored_models_dormant_time;
	bool	colored_models_dormant_fadeout;
	bool	colored_models_paint_players_weapons;
	int		colored_models_players;
	bool	colored_models_players_wireframe;
	bool	colored_models_players_players[3];
	bool	colored_models_players_behind_wall;
	int		colored_models_players_color_health_based;
	float	colored_models_players_color_t_hide[4];
	float	colored_models_players_color_t_vis[4];
	float	colored_models_players_color_ct_hide[4];
	float	colored_models_players_color_ct_vis[4];
	int		colored_models_players_on_the_dead;
	float	colored_models_players_on_the_dead_color[4];
	int		colored_models_players_hit_position;
	float	colored_models_players_hit_position_time;
	float	colored_models_players_hit_position_color[4];
	int		colored_models_players_desync_aa;
	float	colored_models_players_desync_aa_color[4];
	int		colored_models_backtrack;
	bool	colored_models_backtrack_wireframe;
	bool	colored_models_backtrack_players[2];
	bool	colored_models_backtrack_behind_wall;
	float	colored_models_backtrack_color_t_hide[4];
	float	colored_models_backtrack_color_t_vis[4];
	float	colored_models_backtrack_color_ct_hide[4];
	float	colored_models_backtrack_color_ct_vis[4];
	int		colored_models_hands;
	bool	colored_models_hands_wireframe;
	float	colored_models_hands_color[4];
	bool	colored_models_hands_color_rainbow;
	float	colored_models_hands_color_rainbow_speed;
	bool	colored_models_dlight;
	bool	colored_models_dlight_players[3];
	int		colored_models_dlight_origin;
	float	colored_models_dlight_radius;
	float	colored_models_dlight_minlight;
	bool	colored_models_dlight_fading_lighting;
	float	colored_models_dlight_fading_lighting_speed;
	float	colored_models_dlight_color[4];
	bool	colored_models_elight;
	bool	colored_models_elight_players[3];
	float	colored_models_elight_radius;
	float	colored_models_elight_color[4];

	bool	esp_other_local_aa_side_arrows;
	bool	esp_other_local_sniper_crosshair;
	bool	esp_other_local_recoil_point;
	float	esp_other_local_recoil_point_color[4];
	bool	esp_other_local_spread_point;
	float	esp_other_local_spread_point_color[4];
	bool	esp_other_local_spread_circle;
	float	esp_other_local_spread_circle_color[4];
	float	esp_other_local_spread_circle_color2[4];
	bool	esp_other_local_aim_fov;
	float	esp_other_local_aim_fov_color[4];
	float	esp_other_local_aim_fov_color2[4];
	bool	esp_other_local_toggle_status;
	float	esp_other_local_toggle_status_color[4];
	float	esp_other_local_toggle_status_color2[4];

	bool	effects_hud_clear;
	int		effects_thirdperson;
	bind_t	effects_thirdperson_key;
	int		effects_custom_render_fov;
	bool	remove_scope;
};

struct cvars_kreedz
{
	bool	active;
};

struct cvars_misc
{
	bind_t	fakelatency_key;
	bool	fakelatency;
	int		fakelatency_amount;
	bool	namestealer;
	int		namestealer_interval;
	bool	automatic_reload;
	bool	automatic_pistol;
	bool	replace_models_with_original;
	bool	steamid_spoofer;
	bind_t	kb_key;
	bool	kb_enabled;
	bool	kb_friendly_fire;
	bool	kb_conditions[3];
	bool	kb_position_adjustment;
	int		kb_attack_type;
	int		kb_aim_type;
	bool	kb_aim_hitbox[6];
	float	kb_fov;
	float	kb_swing_distance;
	float	kb_stab_distance;
	float	kb_aim_hitbox_scale;
};



namespace cvars
{
	inline cvars_ragebot ragebot;
	inline cvars_legitbot legitbot;
	inline cvars_weapons weapons[1024];
	inline cvars_visuals visuals;
	inline cvars_kreedz kreedz;
	inline cvars_misc misc;
}
