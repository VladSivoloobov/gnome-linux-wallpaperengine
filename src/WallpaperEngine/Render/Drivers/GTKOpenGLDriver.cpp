//
// Created by vladislav on 08.07.2026.
//

#include "GTKOpenGLDriver.h"

GTKOpenGLDriver::GTKOpenGLDriver (const char* windowTitle, ApplicationContext& context, WallpaperApplication& app) :
    VideoDriver (app, m_mouseInput), m_context (context), m_mouseInput (*this){

}