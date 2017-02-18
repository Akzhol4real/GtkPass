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
#include <cstring>
#include <cmath>

/**
 * Constructor of \p GtkPassWindow. Initializes member variables and loads
 * the GUI description from their XML-files.
 * \b Note: Do not use directly. Use \p create() instead!
 *
 * \param cobject The window's base object
 * \param builder Constant reference to a \p Gtk::Builder
 */
GtkPassWindow::GtkPassWindow(
    BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
    Gtk::ApplicationWindow(cobject), m_refBuilder(builder), m_options(),
    m_optionIncludeUpperCase(nullptr), m_optionIncludeLowerCase(nullptr),
    m_optionIncludeNumeric(nullptr), m_optionIncludeSpecial(nullptr),
    m_optionIncludeDash(nullptr), m_optionIncludeSpace(nullptr),
    m_passwordLength(nullptr), m_passwordEntropy(nullptr),
    m_entropyLevel(nullptr), m_passwordEntry(nullptr),
    m_btnShowPassword(nullptr), m_btnGeneratePassword(nullptr),
    m_css(Gtk::CssProvider::create()), m_styleCtx(this->get_style_context()),
    m_screen(Gdk::Screen::get_default()) {

    // store the length of the alphabet strings locally. This is just for
    // convenience and to increase performance. Here we calculate the length
    // only at startup, otherwise we would need to do this for every single
    // update in the GUI.
    m_alphaLength.emplace_back(std::strlen(ALPHA_LETTERS_LOWER));
    m_alphaLength.emplace_back(std::strlen(ALPHA_LETTERS_UPPER));
    m_alphaLength.emplace_back(std::strlen(ALPHA_NUMBERS));
    m_alphaLength.emplace_back(std::strlen(ALPHA_SPACE));
    m_alphaLength.emplace_back(std::strlen(ALPHA_DASH));
    m_alphaLength.emplace_back(std::strlen(ALPHA_SPECIAL));

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

    m_refBuilder->get_widget("entropyValue", m_passwordEntropy);
    if (!m_passwordEntropy) {
        throw std::runtime_error("No \"entropyValue\" object in ui file!");
    }

    m_refBuilder->get_widget("entropyLevelBar", m_entropyLevel);
    if (!m_entropyLevel) {
        throw std::runtime_error("No \"entropyLevelBar\" object in ui file!");
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

    // connect check boxes to signal handler
    m_optionIncludeLowerCase->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );
    m_optionIncludeUpperCase->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );
    m_optionIncludeNumeric->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );
    m_optionIncludeSpace->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );
    m_optionIncludeDash->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );
    m_optionIncludeSpecial->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_check)
    );

    // initialization of password length spinbutton
    m_passwordLengthAdjustment = Gtk::Adjustment::create(
        12.0, /* value */ 1.0, /* lower bound */ 100.0, /* upper bound */
        1.0 /* step increment */
    );
    m_passwordLength->set_adjustment(m_passwordLengthAdjustment);
    m_passwordLength->set_wrap(false);
    m_passwordLength->signal_changed().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_lengthChanged)
    );

    // add signal handler for clicking the generate button
    m_btnGeneratePassword->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::generatePassword)
    );
    // add signal handler for clicking the toggle button
    m_btnShowPassword->signal_clicked().connect(
        sigc::mem_fun(*this, &GtkPassWindow::on_clickToggleButton)
    );
    updateEntropy();
}

/**
 * Creates a new instance of \p GtkPassWindow and returns a pointer to it.
 * Use this method instead of the constructore directly.
 * This function gets a compiled resource from the file \p resources.c in
 * order to build the window. If the resource could not be loaded, an exception
 * of type \p std::runtime_error will be thrown.
 *
 * \throws std::runtime_error if compiled resource could not be loaded.
 * \return Pointer to the new instance of \p GtkPassWindow
 */
GtkPassWindow* GtkPassWindow::create() {
    auto refBuilder = Gtk::Builder::create_from_resource("/org/darth-revan/gtkpass/window.ui");
    GtkPassWindow* window = nullptr;
    refBuilder->get_widget_derived("applicationWindow", window);
    if (!window) {
        throw std::runtime_error("No \"applicationWindow\" object in resource!");
    }
    return window;
}

/**
 * Signal handler for changing the state of one of the checkboxes. Updates the
 * state of the member variable \p m_options.
 */
void GtkPassWindow::on_check() {
    m_options.bIncludeLettersLower = m_optionIncludeLowerCase->get_active();
    m_options.bIncludeLettersUpper = m_optionIncludeUpperCase->get_active();
    m_options.bIncludeNumbers = m_optionIncludeNumeric->get_active();
    m_options.bIncludeSpace = m_optionIncludeSpace->get_active();
    m_options.bIncludeDash = m_optionIncludeDash->get_active();
    m_options.bIncludeSpecial = m_optionIncludeSpecial->get_active();
    updateEntropy();
}

/**
 * Signal handler for clicking the generate button. Generates a password
 * with the user's options and writes it into the password text field.
 */
void GtkPassWindow::generatePassword() {
    m_passwordEntry->set_text(
        getRandomString(static_cast<uint32_t>(m_passwordLength->get_value()), m_options)
    );
}

/**
 * Signal handler for clicking the toggle button to show the password. Gets the
 * state of the toggle button and shows or hides the password.
 */
void GtkPassWindow::on_clickToggleButton() {
    m_passwordEntry->set_visibility(m_btnShowPassword->get_active());
}

/**
 * Calculates the possible password entropy and updates the widgets in the
 * GUI.
 */
void GtkPassWindow::updateEntropy() {
    double entropy {0};
    unsigned long value {};
    std::string cssData;

    // add length of alphabet strings
    if (m_options.bIncludeLettersLower)
        entropy += m_alphaLength[0];
    if (m_options.bIncludeLettersUpper)
        entropy += m_alphaLength[1];
    if (m_options.bIncludeNumbers)
        entropy += m_alphaLength[2];
    if (m_options.bIncludeSpace)
        entropy += m_alphaLength[3];
    if (m_options.bIncludeDash)
        entropy += m_alphaLength[4];
    if (m_options.bIncludeSpecial)
        entropy += m_alphaLength[5];

    // calculate entropy: entropy = log2(pow(numberOfChars, length))
    entropy = std::pow(entropy, m_passwordLength->get_value());
    entropy = std::ceil(std::log2(entropy));
    value = static_cast<unsigned long>(entropy);
    m_passwordEntropy->set_text("~ " + std::to_string(value) + " Bit");

    // set the password quality level
    if (value < 64) {
        m_entropyLevel->set_value(1.0);
        cssData = m_cssLvl1;
    } else if (value >= 64 && value < 80) {
        m_entropyLevel->set_value(2.0);
        cssData = m_cssLvl2;
    } else if (value >= 80 && value < 96) {
        m_entropyLevel->set_value(3.0);
        cssData = m_cssLvl3;
    } else if (value >= 96 && value < 112) {
        m_entropyLevel->set_value(4.0);
        cssData = m_cssLvl4;
    } else {
        m_entropyLevel->set_value(5.0);
        cssData = m_cssLvl5;
    }

    // update the color of the level bar by applying css style
    m_css->load_from_data(cssData);
    m_styleCtx->add_provider_for_screen(m_screen, m_css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * Signal handler for changing the length value of the password. Updates the
 * entropy.
 */
void GtkPassWindow::on_lengthChanged() {
    updateEntropy();
}
