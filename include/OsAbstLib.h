/*
    Copyright (C) 2021 Adrien Saad

    This file is part of OsAbstLibrary.

    OsAbstLibrary is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OsAbstLibrary is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with OsAbstLibrary. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file OsAbstLib.h
 * @brief Main header. When using the library, include this header instead of the smaller ones.
 */

/** \mainpage OsAbstLib
 *
 * This library provides OS-neutral functions for several specific tasks. This includes POSIX
 * functions not available on Windows or functions retrieving OS specific paths such as the user
 * data path.
 */

#include "OAL_error.h"
#include "os_dir.h"
#include "os_file.h"
#include "os_paths.h"
#include "os_string.h"
#include "os_type.h"
