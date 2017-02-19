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
#include <vector>

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

    /// Holds the length of the alphabet strings
    std::vector<size_t> m_alphaLength;

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
    /// Label displaying the number of chars in input set
    Gtk::Label* m_characterCount;

    /// Pointer to the spin button controlling the length of the password
    Gtk::SpinButton* m_passwordLength;
    /// \p Glib::RefPtr to the \p Gtk::Adjustment of the password length spin
    /// button
    Glib::RefPtr<Gtk::Adjustment> m_passwordLengthAdjustment;

    /// Pointer to the label displaying the password's entropy
    Gtk::Label* m_passwordEntropy;
    /// Pointer to the entropy level bar
    Gtk::LevelBar* m_entropyLevel;

    /// Pointer to the entry field holding the password
    Gtk::Entry* m_passwordEntry;
    /// Pointer to the toggle button for showing and hiding the password
    Gtk::ToggleButton* m_btnShowPassword;
    /// Pointer to the button for generating the password
    Gtk::Button* m_btnGeneratePassword;

    /// Intelligent Pointer to a \p Gtk::CssProvider
    Glib::RefPtr<Gtk::CssProvider> m_css;
    /// Intelligent Pointer to the style context
    Glib::RefPtr<Gtk::StyleContext> m_styleCtx;
    /// Intelligent Pointer to the default screen
    Glib::RefPtr<Gdk::Screen> m_screen;

    /// String storing the CSS data for red level bar
    const std::string m_cssLvl1 = ".level-bar.fill-block.level-high {"
        "    border-color: red;"
        "    background-color: red;"
        "}";
    /// String storing the CSS data for orange level bar
    const std::string m_cssLvl2 = ".level-bar.fill-block.level-high {"
        "    border-color: orange;"
        "    background-color: orange;"
        "}";
    /// String storing the CSS data for yellow level bar
    const std::string m_cssLvl3 = ".level-bar.fill-block.level-high {"
        "    border-color: yellow;"
        "    background-color: yellow;"
        "}";
    /// String storing the CSS data for yellow green level bar
    const std::string m_cssLvl4 = ".level-bar.fill-block.level-high {"
        "    border-color: yellowgreen;"
        "    background-color: yellowgreen;"
        "}";
    /// String storing the CSS data for green level bar
    const std::string m_cssLvl5 = ".level-bar.fill-block.level-high {"
        "    border-color: green;"
        "    background-color: green;"
        "}";

    /// Signal handler for checking the check boxes
    void on_check();
    /// Signal handler for clicking the generate button
    void generatePassword();
    /// Signal handler for clicking the show password button
    void on_clickToggleButton();
    /// Signal handler for changing the password length
    void on_lengthChanged();

    /// Function for calculating the possible password entropy and updating the
    /// widgets displaying it
    void updateEntropy();

}; // End of class GtkPassWindow

#endif
