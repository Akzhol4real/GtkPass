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
 * \file    main.cpp
 * \brief   Main file of GtkPass providing the function \p main.
 * \author  Kevin Kirchner
 * \date    2017
 * \copyright GNU GPL Version 3
 *
 * This file is the main source file of GtkPass and provides the function
 * \p main.
 */

// check for autotools config.h
#ifdef HAVE_CONFIG_H
#   include <config.h>
#else
#   error "Do no compile without Autotools!"
#endif

#include "RandomGenerator.h"
#include "Application.h"
#include <iostream>

/**
 *  Main function executed at application start.
 *
 * \param argc Number of command line arguments
 * \param argv Array of strings containing the command line arguments
 * \return Integer value indicating success
 */
int main(int argc, char* argv[]) {
    if (sodium_init() == 1) {
        std::cerr << "ERROR: Failed to initialize libsodium!" << std::endl;
        return 1;
    }
    auto application = GtkPassApplication::create();
    return application->run(argc, argv);
}
