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
 * \file    RandomGenerator_Test.cpp
 * \brief   Tests the files \p RandomGenerator.h and \p RandomGenerator.cpp.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * Tests the files \p RandomGenerator.h and \p RandomGenerator.cpp.
 */

#include "catch.hpp"
#include "RandomGenerator.h"
#include <map>

/// Tests the function \p getRandomNumber of \p RandomGenerator
TEST_CASE("getRandomNumber", "[RandomGenerator]") {
    size_t testSize = 20;
    uint32_t bound = 10;

    SECTION("Unique values") {
        std::map<uint32_t, int> numbers;
        for (size_t i = 0; i < testSize; i++) {
            ++numbers[getRandomNumber()];
        }
        REQUIRE(numbers.size() == testSize);
        for (const auto& elem : numbers) {
            REQUIRE(elem.second == 1);
        }
        numbers.clear();
    }

    SECTION("Random numbers with bounds") {
        uint32_t num;
        for (size_t i = 0; i < testSize; i++) {
            num = getRandomNumber(bound);
            REQUIRE(num < bound);
        }
    }
}

/// Tests the function \p getRandomString of \p RandomGenerator
TEST_CASE("getRandomString", "[RandomGenerator]") {
    size_t testSize = 20;
    uint32_t bound = 10;
    std::string randString;
    genopts options;

    SECTION("Default options") {
        REQUIRE(options.bIncludeLettersUpper == true);
        REQUIRE(options.bIncludeLettersLower == true);
        REQUIRE(options.bIncludeNumbers == true);
        REQUIRE(options.bIncludeDash == false);
        REQUIRE(options.bIncludeSpace == false);
        REQUIRE(options.bIncludeSpecial == false);
    }

    SECTION("Length") {
        for (size_t i = 0; i < testSize; i++) {
            randString = getRandomString(bound, options);
            REQUIRE(randString.length() == bound);
        }
    }

    SECTION("Contents") {
        testSize = 10;
        for (size_t i = 0; i < testSize; i++) {
            randString = getRandomString(bound, options);
            REQUIRE(randString.find_first_of(ALPHA_DASH) == std::string::npos);
            REQUIRE(randString.find_first_of(ALPHA_SPACE) == std::string::npos);
            REQUIRE(randString.find_first_of(ALPHA_SPECIAL) == std::string::npos);
        }

        options.bIncludeSpecial = true;
        for (size_t i = 0; i < testSize; i++) {
            randString = getRandomString(bound, options);
            REQUIRE(randString.find_first_of(ALPHA_DASH) == std::string::npos);
            REQUIRE(randString.find_first_of(ALPHA_SPACE) == std::string::npos);
        }
    }
}

/// Test case for the function \p removeFromString
TEST_CASE("removeFromString", "[RandomGenerator]") {
    std::string str = "Test";
    std::string toRem = "es";

    removeFromString(str, toRem);
    REQUIRE(str.length() == 2);
    REQUIRE(str.compare("Tt") == 0);

    str = "Hello World";
    toRem = "l";
    removeFromString(str, toRem);
    REQUIRE(str.compare("Heo Word") == 0);

    str = "This is a test";
    toRem = "tt";
    removeFromString(str, toRem);
    REQUIRE(str.compare("This is a es") == 0);
}
