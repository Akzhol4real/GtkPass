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
 * \file    Application.h
 * \brief   Defines the application class for \p GtkPass.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file defines the application class for \p GtkPass.
 */

#ifndef GTKPASS_APPLICATION_H
#define GTKPASS_APPLICATION_H

#include "MainWindow.h"

/// GtkPass' application class as a subclass of \p Gtk::Application
class GtkPassApplication : public Gtk::Application {

public:
    static Glib::RefPtr<GtkPassApplication> create();

protected:
    GtkPassApplication();
    void on_activate() override;

private:
    GtkPassWindow* createApplicationWindow();
    void on_hide_window(Gtk::Window* window);

}; // end of class GtkPassApplication

#endif
