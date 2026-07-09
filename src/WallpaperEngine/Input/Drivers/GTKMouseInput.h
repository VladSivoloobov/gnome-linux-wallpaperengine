//
// Created by vladislav on 08.07.2026.
//
#pragma once

#ifndef LINUX_WALLPAPERENGINE_GTKMOUSEINPUT_H
#define LINUX_WALLPAPERENGINE_GTKMOUSEINPUT_H
#include "WallpaperEngine/Audio/Drivers/AudioDriver.h"
#include "WallpaperEngine/Input/MouseInput.h"

#include <glm/vec2.hpp>

namespace WallpaperEngine::Render::Drivers {
class GTKOpenGLDriver;
}

namespace WallpaperEngine::Input::Drivers {
class GTKMouseInput final : public MouseInput {
public:
    explicit GTKMouseInput (const Render::Drivers::GTKOpenGLDriver& driver);
    void update() override;
    [[nodiscard]] glm::dvec2 position() const override;
    [[nodiscard]] MouseClickStatus leftClick() const override;
    [[nodiscard]] MouseClickStatus rightClick() const override;
private:
    const Render::Drivers::GTKOpenGLDriver* m_driver;

    glm::dvec2 m_mousePosition = {};
    glm::dvec2 m_reportedPosition = {};
    MouseClickStatus m_leftClick = Released;
    MouseClickStatus m_rightClick = Released;
};
}

#endif // LINUX_WALLPAPERENGINE_GTKMOUSEINPUT_H
