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
 * \file    RandomGenerator.cpp
 * \brief   Implements functions for generating random numbers and strings with
 *          libsodium.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file implements functions for generating random numbers and strings with
 * libsodium.
 */

#include "RandomGenerator.h"
#include <sstream>
#include <algorithm>

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
uint32_t getRandomNumber(uint32_t upperBound) {
    if (upperBound == 0) {
        return randombytes_random();
    } else {
        return randombytes_uniform(upperBound);
    }
}

/**
 * Generates a random string by using a random number returned by
 * \p getRandomNumber(). The string will contain \p length characters and will
 * meet the requirements in \p options.
 *
 * \param length The number of characters in the string
 * \param options The options for generating the string
 * \return Random string
 */
std::string getRandomString(const unsigned int length, const genopts& options){
    std::stringstream alphabet;
    if (length <= 0)
        return "";

    // include alphabet characters based on options
    if (options.bIncludeLettersLower)
        alphabet << ALPHA_LETTERS_LOWER;
    if (options.bIncludeLettersUpper)
        alphabet << ALPHA_LETTERS_UPPER;
    if (options.bIncludeNumbers)
        alphabet << ALPHA_NUMBERS;
    if (options.bIncludeSpace)
        alphabet << ALPHA_SPACE;
    if (options.bIncludeDash)
        alphabet << ALPHA_DASH;
    if (options.bIncludeSpecial)
        alphabet << ALPHA_SPECIAL;

    // get the alphabet string
    std::string alpha = alphabet.str();

    // remove characters from alphabet when avoiding similar
    if (options.bAvoidSimilarChars)
        removeFromString(alpha, ALPHA_SIMILAR);

    if (alpha.length() <= 0)
        return "";

    std::stringstream randomString;

    // generate the random string
    for (unsigned int i = 0; i < length; i++) {
        randomString << alpha[getRandomNumber() % (alpha.length() - 1)];
    }

    return randomString.str();
}

/**
 * Takes a reference to a string and removes all characters in \p toRemove in
 * it. The result will directly be written to the variable.
 *
 * \param str The string to remove chars from
 * \param toRemove String consisting of the characters to remove
 */
void removeFromString(std::string& str, const std::string& toRemove) {
    for (size_t i = 0; i < toRemove.length(); i++) {
        str.erase(remove(str.begin(), str.end(), toRemove[i]), str.end());
    }
}
