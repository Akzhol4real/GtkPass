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

#include "RandomGenerator.h"
#include <gtkmm.h>

class GtkPassWindow : public Gtk::ApplicationWindow {

public:
    GtkPassWindow(BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& builder);
    static GtkPassWindow* create();

private:
    /// \p Glib::RefPtr to a \p Gtk::Builder for GUI construction
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    /// Options to use for password generation;
    genopts m_options;

    /// Pointer to check button for including upper case characters
    Gtk::CheckButton* m_optionIncludeUpperCase;
    /// Pointer to check button for including lower case characters
    Gtk::CheckButton* m_optionIncludeLowerCase;
    /// Pointer to check button for including numbers
    Gtk::CheckButton* m_optionIncludeNumeric;
    /// Pointer to check button for including special characters
    Gtk::CheckButton* m_optionIncludeSpecial;
    /// Pointer to check button for including dash character
    Gtk::CheckButton* m_optionIncludeDash;
    /// Pointer to check button for including space character
    Gtk::CheckButton* m_optionIncludeSpace;

    /// Pointer to the spin button controlling the length of the password
    Gtk::SpinButton* m_passwordLength;
    /// Pointer to the spin button displaying the password's entropy
    Gtk::SpinButton* m_passwordEntropy;

    /// Pointer to the entry field holding the password
    Gtk::Entry* m_passwordEntry;
    /// Pointer to the toggle button for showing and hiding the password
    Gtk::ToggleButton* m_btnShowPassword;
    /// Pointer to the button for generating the password
    Gtk::Button* m_btnGeneratePassword;

}; // End of class GtkPassWindow

#endif
