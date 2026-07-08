//
// Created by vladislav on 08.07.2026.
//
#pragma once
#include "GTKOpenGLDriver.h"

#include "GTKOpenGLDriverWindow.h"
#include "VideoFactories.h"

using namespace WallpaperEngine::Render::Drivers;
using namespace WallpaperEngine::Windows;

GTKOpenGLDriver::GTKOpenGLDriver (const char* windowTitle, ApplicationContext& context, WallpaperApplication& app) :
    VideoDriver (app, m_mouseInput), m_context (context), m_mouseInput (*this) {

    if (const int gtk_app_status = this->create_gtk_window (); gtk_app_status != 0) {
	throw std::runtime_error (std::format ("GTK Window is not opened, status: {0}", gtk_app_status));
    }
}

int GTKOpenGLDriver::create_gtk_window () {
    auto gtk_app = Gtk::Application::create ("org.gtkmm.examples.base", Gio::Application::Flags::NON_UNIQUE);

    gtk_app->signal_activate ().connect ([&gtk_app] () {
	const auto window = new GTKOpenGLDriverWindow ();
	gtk_app->add_window (*window);
	window->set_visible (true);
    });

    return gtk_app->run ();
}

__attribute__ ((constructor)) void registerGTKOpenGL () {
    sVideoFactories.registerDriver (
	ApplicationContext::DESKTOP_BACKGROUND, "wayland",
	[] (ApplicationContext& context, WallpaperApplication& app) -> std::unique_ptr<VideoDriver> {
	    return std::make_unique<GTKOpenGLDriver> (context, app);
	}
    );
}