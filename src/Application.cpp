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
#include <vector>

/**
 * Constructor of p GtkPassApplication. Initializes the base object and sets
 * its D-Bus name to "org.darth-revan.gtkpass".
 */
GtkPassApplication::GtkPassApplication() :
    Gtk::Application("org.darth-revan.gtkpass")
    {
        // set information for about dialog on startup
        m_aboutDialog.set_program_name(PACKAGE_NAME);
        m_aboutDialog.set_version(PACKAGE_VERSION);
        m_aboutDialog.set_comments("A password generator with GTK-based graphical user interface.");
        m_aboutDialog.set_license_type(Gtk::LICENSE_GPL_3_0);
        m_aboutDialog.set_copyright(PROGRAM_AUTHOR);
        m_aboutDialog.set_website("https://github.com/Darth-Revan/GtkPass");
        m_aboutDialog.set_website_label("Visit on GitHub");
        m_aboutDialog.set_logo_icon_name("gtk-pass");

        std::vector<Glib::ustring> v_authors;
        v_authors.push_back(PROGRAM_AUTHOR);
        m_aboutDialog.set_authors(v_authors);
    }


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
 * Overrides standard handler for \p on_startup(). Calls the original function
 * and builds the application's menu by using a \p Gtk::Builder.
 */
void GtkPassApplication::on_startup() {
    Gtk::Application::on_startup();
    add_action("about",
        sigc::mem_fun(*this, &GtkPassApplication::on_actionAbout));

    // create the builder
    auto refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_resource("/org/darth-revan/gtkpass/appMenu.ui");
    } catch (const Glib::Error& ex) {
        std::cerr << "GtkPassApplication::on_startup(): " << ex.what()
            << std::endl;
        return;
    }

    // load the menu from resource and set it as menu
    auto obj = refBuilder->get_object("appmenu");
    auto appMenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(obj);
    if (appMenu)
        set_app_menu(appMenu);
    else
        std::cerr << "GtkPassApplication::on_startup(): No \"appmenu\" object in appMenu.ui!" << std::endl;
}

/**
 * Signal handler for hiding the application's window.
 *
 * \param window Pointer to the window that gets hidden.
 */
void GtkPassApplication::on_hide_window(Gtk::Window* window) {
    delete window;
}

/**
 * Handler for clicking on the menu item "About". Shows a simple about dialog
 * for the application.
 */
void GtkPassApplication::on_actionAbout() {
    m_aboutDialog.set_transient_for(*(this->get_active_window()));
    m_aboutDialog.show();
    m_aboutDialog.present();
}
