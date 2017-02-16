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
 * \file    MainWindow.h
 * \brief   Defines the main window for \p GtkPass.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file defines the main window for \p GtkPass.
 */

#ifndef GTKPASS_MAINWINDOW_H
#define GTKPASS_MAINWINDOW_H

#include <gtkmm.h>

class GtkPassWindow : public Gtk::ApplicationWindow {

public:
    GtkPassWindow(BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& builder);
    static GtkPassWindow* create();

private:
    /// \p Glib::RefPtr to a \p Gtk::Builder for GUI construction
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

}; // End of class GtkPassWindow

#endif
