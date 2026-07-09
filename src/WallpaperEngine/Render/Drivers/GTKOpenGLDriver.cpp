//
// Created by vladislav on 08.07.2026.
//
#include "GTKOpenGLDriver.h"
#include "VideoFactories.h"
#include "WallpaperEngine/Render/Drivers/VideoDriver.h"

using namespace WallpaperEngine::Render::Drivers;

GTKOpenGLDriver::GTKOpenGLDriver (const char* windowTitle, ApplicationContext& context, WallpaperApplication& app) :
    VideoDriver (app, m_mouseInput), m_context (context), m_mouseInput (*this) {

    create_gtk_window (windowTitle);
}

Glib::RefPtr<Gtk::Application> GTKOpenGLDriver::create_gtk_window (const char* windowTitle) {
    setenv ("GDK_BACKEND", "x11", 1);

    Glib::RefPtr<Gtk::Application> gtk_app
	= Gtk::Application::create ("org.gtkmm.examples.base", Gio::Application::Flags::NON_UNIQUE);

    gtk_app->signal_activate ().connect ([&gtk_app, windowTitle, this] () {
	this->m_window = new Gtk::Window {};
	this->m_glArea = new Gtk::GLArea {};

	this->m_window->set_type_hint (Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DESKTOP);

	this->m_window->set_title (windowTitle);
	this->m_window->set_visible (true);
	this->m_window->add (*this->m_glArea);

	this->m_glArea->signal_render ().connect (sigc::mem_fun (*this, &GTKOpenGLDriver::on_glarea_render));
	this->m_glArea->signal_realize ().connect (sigc::mem_fun (*this, &GTKOpenGLDriver::on_glarea_realize));

	gtk_app->add_window (*this->m_window);
    });

    this->m_gtkThread = std::thread ([gtk_app] { gtk_app->run (); });

    return gtk_app;
}

__attribute__ ((constructor)) void registerGTKOpenGL () {
    sVideoFactories.registerDriver (
	ApplicationContext::DESKTOP_BACKGROUND, "x11",
	[] (ApplicationContext& context, WallpaperApplication& application) -> std::unique_ptr<VideoDriver> {
	    return std::make_unique<GTKOpenGLDriver> ("wallpaperengine", context, application);
	}
    );
}