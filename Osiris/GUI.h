#pragma once

#include <memory>

struct ImFont;

class GUI {
public:
    GUI() noexcept;
    void render() noexcept;
    void handleToggle() noexcept;
    void updateColors() const noexcept;
    [[nodiscard]] bool isOpen() const noexcept { return open; }
private:
    bool open = true;

    
    void renderMenuBar() noexcept;
    void renderAimbotWindow(bool contentOnly = false) noexcept;
    void renderTriggerbotWindow(bool contentOnly = false) noexcept;
    void renderChamsWindow(bool contentOnly = false) noexcept;
    void renderStyleWindow(bool contentOnly = false) noexcept;
    void renderConfigWindow(bool contentOnly = false) noexcept;
    void renderGuiStyle2() noexcept;

    struct {
        bool aimbot = false;
        bool triggerbot = false;
        bool chams = false;
        bool sound = false;
        bool style = false;
        bool config = false;
    } window;

    struct {
        ImFont* normal15px = nullptr;
    } fonts;

    float timeToNextConfigRefresh = 0.1f;
};

inline std::unique_ptr<GUI> gui;


extern void thats_what_i_say(int& currentConfig, bool& incrementalLoad, std::vector<std::u8string>& configItems, std::u8string& buffer, ImVec2 button_size);
extern void new_chams_1();

extern void new_chams_2();
extern void new_chams_3();
extern void new_chams_4();
extern void new_chams_5();
extern void new_chams_6();
extern void trigger_1();