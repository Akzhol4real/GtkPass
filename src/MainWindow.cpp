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
#include <iostream>

/// Constructor of \p GtkPassWindow. Initializes member variables and loads
/// the GUI description from their XML-files.
/// \b Note: Do not use directly. Use \p create() instead!
///
/// \param cobject The window's base object
/// \param builder Constant reference to a \p Gtk::Builder
GtkPassWindow::GtkPassWindow(
    BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
    Gtk::ApplicationWindow(cobject), m_refBuilder(builder), m_options(),
    m_optionIncludeUpperCase(nullptr), m_optionIncludeLowerCase(nullptr),
    m_optionIncludeNumeric(nullptr), m_optionIncludeSpecial(nullptr),
    m_optionIncludeDash(nullptr), m_optionIncludeSpace(nullptr),
    m_passwordLength(nullptr), m_passwordEntropy(nullptr),
    m_passwordEntry(nullptr), m_btnShowPassword(nullptr),
    m_btnGeneratePassword(nullptr) {

    m_refBuilder->get_widget("optionIncludeUpperCase", m_optionIncludeUpperCase);
    if (!m_optionIncludeUpperCase) {
        throw std::runtime_error("No \"optionIncludeUpperCase\" object in ui file!");
    }

    m_refBuilder->get_widget("optionIncludeLowerCase", m_optionIncludeLowerCase);
    if (!m_optionIncludeLowerCase) {
        throw std::runtime_error("No \"optionIncludeLowerCase\" object in ui file!");
    }

    m_refBuilder->get_widget("optionIncludeNumeric", m_optionIncludeNumeric);
    if (!m_optionIncludeNumeric) {
        throw std::runtime_error("No \"optionIncludeNumeric\" object in ui file!");
    }

    m_refBuilder->get_widget("optionIncludeSpecial", m_optionIncludeSpecial);
    if (!m_optionIncludeSpecial) {
        throw std::runtime_error("No \"optionIncludeSpecial\" object in ui file!");
    }

    m_refBuilder->get_widget("optionIncludeDash", m_optionIncludeDash);
    if (!m_optionIncludeDash) {
        throw std::runtime_error("No \"optionIncludeDash\" object in ui file");
    }

    m_refBuilder->get_widget("optionIncludeSpace", m_optionIncludeSpace);
    if (!m_optionIncludeSpace) {
        throw std::runtime_error("No \"optionIncludeSpace\" object in ui file");
    }

    m_refBuilder->get_widget("passwordLength", m_passwordLength);
    if (!m_passwordLength) {
        throw std::runtime_error("No \"passwordLength\" object in ui file!");
    }

    m_refBuilder->get_widget("passwordEntropy", m_passwordEntropy);
    if (!m_passwordEntropy) {
        throw std::runtime_error("No \"passwordEntropy\" object in ui file!");
    }

    m_refBuilder->get_widget("entryPassword", m_passwordEntry);
    if (!m_passwordEntry) {
        throw std::runtime_error("No \"entryPassword\" object in ui file!");
    }

    m_refBuilder->get_widget("btnShowPassword", m_btnShowPassword);
    if (!m_btnShowPassword) {
        throw std::runtime_error("No \"btnShowPassword\" object in ui file!");
    }

    m_refBuilder->get_widget("btnGeneratePassword", m_btnGeneratePassword);
    if (!m_btnGeneratePassword) {
        throw std::runtime_error("No \"btnGeneratePassword\" object in ui file!");
    }


    // set the default options
    m_optionIncludeLowerCase->set_active(m_options.bIncludeLettersLower);
    m_optionIncludeUpperCase->set_active(m_options.bIncludeLettersUpper);
    m_optionIncludeNumeric->set_active(m_options.bIncludeNumbers);
    m_optionIncludeSpecial->set_active(m_options.bIncludeSpecial);
    m_optionIncludeSpace->set_active(m_options.bIncludeSpace);
    m_optionIncludeDash->set_active(m_options.bIncludeDash);

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
