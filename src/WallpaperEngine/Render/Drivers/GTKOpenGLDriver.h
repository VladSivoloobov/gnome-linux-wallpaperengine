//
// Created by vladislav on 08.07.2026.
//
#pragma once
#include "WallpaperEngine/Input/Drivers/GTKMouseInput.h"
#include "WallpaperEngine/Render/CWallpaper.h"
#include <gtkmm.h>

using namespace WallpaperEngine::Render::Drivers;
using namespace WallpaperEngine::Application;

namespace WallpaperEngine::Render::Drivers {
class GTKOpenGLDriver final : public VideoDriver {
public:
    explicit GTKOpenGLDriver (const char* windowTitle, ApplicationContext& context, WallpaperApplication& app);
    ~GTKOpenGLDriver () override;

    [[nodiscard]] Output::Output& getOutput () override;
    [[nodiscard]] float getRenderTime () const override;
    bool closeRequested () override;
    void resizeWindow (glm::ivec2 size) override;
    void resizeWindow (glm::ivec4 positionAndSize) override;
    void showWindow () override;
    void hideWindow () override;
    [[nodiscard]] glm::ivec2 getFramebufferSize () const override;
    [[nodiscard]] uint32_t getFrameCounter () const override;
    void dispatchEventQueue () override;
    [[nodiscard]] void* getProcAddress (const char* name) const override;

    Gtk::Window* getWindow () const;

private:
    ApplicationContext& m_context;
    WallpaperEngine::Input::Drivers::GTKMouseInput m_mouseInput;
    Output::Output* m_output = nullptr;
    Gtk::Window* m_window = nullptr;
    uint32_t m_frameCounter = 0;
    static int create_gtk_window();
};
}
