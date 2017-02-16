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
 * \file    MainWindow.cpp
 * \brief   Implements the main window for \p GtkPass.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file implements the main window for \p GtkPass.
 */

#include "MainWindow.h"
#include <stdexcept>

/// Constructor of \p GtkPassWindow. Initializes member variables and loads
/// the GUI description from their XML-files.
/// \b Note: Do not use directly. Use \p create() instead!
///
/// \param cobject The window's base object
/// \param builder Constant reference to a \p Gtk::Builder
GtkPassWindow::GtkPassWindow(
    BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
    Gtk::ApplicationWindow(cobject), m_refBuilder(builder) {

}

/// Creates a new instance of \p GtkPassWindow and returns a pointer to it.
/// Use this method instead of the constructore directly.
/// This function gets a compiled resource from the file \p resources.c in
/// order to build the window. If the resource could not be loaded, an exception
/// of type \p std::runtime_error will be thrown.
///
/// \throws std::runtime_error if compiled resource could not be loaded.
/// \return Pointer to the new instance of \p GtkPassWindow
GtkPassWindow* GtkPassWindow::create() {
    auto refBuilder = Gtk::Builder::create_from_resource("/org/darth-revan/gtkpass/window.ui");
    GtkPassWindow* window = nullptr;
    refBuilder->get_widget_derived("applicationWindow", window);
    if (!window) {
        throw std::runtime_error("No \"applicationWindow\" object in resource!");
    }
    return window;
}
