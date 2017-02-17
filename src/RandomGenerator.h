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
 * \file    RandomGenerator.h
 * \brief   Defines functions for generating random numbers and strings with
 *          libsodium.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file defines functions for generating random numbers and strings with
 * libsodium.
 */

#ifndef GTKPASS_RANDOMGEN_H
#define GTKPASS_RANDOMGEN_H

#include "sodium.h"
#include <string>

/// Defines lower case characters
#define ALPHA_LETTERS_LOWER "abcdefghijklmnopqrstuvwxyz"
/// Defines upper case characters
#define ALPHA_LETTERS_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
/// Defines numeric characters
#define ALPHA_NUMBERS "0123456789"
/// Defines the space character
#define ALPHA_SPACE " "
/// Defines the dash character
#define ALPHA_DASH "-"
/// Defines ASCII special characters (without dash and space)
#define ALPHA_SPECIAL "!\"#$%&'()*+,./<=>?@:;\\[]^`{}|~"

/**
 * \typedef genopts
 * \brief Defines a struct holding options for generating random strings.
 */
typedef struct options {
    /// Initializes the struct with default options:
    /// \li \p bIncludeLettersLower = true
    /// \li \p bIncludeLettersUpper = true
    /// \li \p bIncludeNumbers = true
    /// \li \p bIncludeDash = false
    /// \li \p bIncludeSpace = false
    /// \li \p bIncludeSpecial = false
    options() : bIncludeLettersLower(true), bIncludeLettersUpper(true),
        bIncludeNumbers(true), bIncludeSpace(false), bIncludeDash(false),
        bIncludeSpecial(false) {}
    /// include lower case characters
    bool bIncludeLettersLower;
    /// include upper case letters
    bool bIncludeLettersUpper;
    /// include numerical numbers
    bool bIncludeNumbers;
    /// include space character
    bool bIncludeSpace;
    /// include dash character
    bool bIncludeDash;
    /// include special characters
    bool bIncludeSpecial;
} genopts;

/**
 * Generates a random unsigned integer with sodium and returns it as
 * \p uint32_t.
 * The optional parameter \p upperBound can be used to set the upper bound for
 * generated numbers. If \p upperBound is 0 the bound will be ignored.
 *
 * \param upperBound Upper bound for the generated number
 * \return Random number between 0 and \p upperBound (or 0xFFFFFFFF if
 * \p upperBound is 0)
 */
uint32_t getRandomNumber(uint32_t upperBound = 0);

/**
 * Generates a random string by using a random number returned by
 * \p getRandomNumber(). The string will contain \p length characters and will
 * meet the requirements in \p options.
 *
 * \param length The number of characters in the string
 * \param options The options for generating the string
 * \return Random string
 */
std::string getRandomString(const unsigned int length, const genopts& options);

#endif
