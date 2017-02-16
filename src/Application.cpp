/* Copyright (C) 2017 Kevin Kirchner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file    Application.cpp
 * \brief   Implements the application class for \p GtkPass.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file implements the application class for \p GtkPass.
 */

#include "Application.h"
#include <config.h>
#include <iostream>

/**
 * Constructor of p GtkPassApplication. Initializes the base object and sets
 * its D-Bus name to "org.darth-revan.gtkpass".
 */
GtkPassApplication::GtkPassApplication() :
    Gtk::Application("org.darth-revan.gtkpass")
    {}


/**
 * Creates a new instance of \p GtkPassApplication and returns an intelligent
 * pointer to the new instance.
 *
 * \return \p Glib::RefPtr to a new instance of \p GtkPassApplication
 */
Glib::RefPtr<GtkPassApplication> GtkPassApplication::create() {
    return Glib::RefPtr<GtkPassApplication>(new GtkPassApplication());
}

/**
 * Creates the application's main window and attaches it to the application.
 * Additionally it attaches a signal for hiding the application and its window.
 *
 * \return Pointer to the application's window
 */
GtkPassWindow* GtkPassApplication::createApplicationWindow() {
    auto appWindow = GtkPassWindow::create();
    add_window(*appWindow);
    appWindow->signal_hide().connect(
        sigc::bind<Gtk::Window*>(sigc::mem_fun(
            *this, &GtkPassApplication::on_hide_window), appWindow
        )
    );
    return appWindow;
}

/**
 * Overrides default signal hanlder for activating the application. Creates the
 * application's main window, sets its title and displays it.
 */
void GtkPassApplication::on_activate() {
    try {
        auto appWindow = createApplicationWindow();
        appWindow->set_title(PACKAGE_NAME);
        appWindow->present();
    } catch (const Glib::Error& ex) {
        std::cerr << "GtkPassApplication::on_activate(): " << ex.what()
            << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "GtkPassApplication::on_activate(): " << ex.what()
            << std::endl;
    }
}

/**
 * Signal handler for hiding the application's window.
 *
 * \param window Pointer to the window that gets hidden.
 */
void GtkPassApplication::on_hide_window(Gtk::Window* window) {
    delete window;
}
