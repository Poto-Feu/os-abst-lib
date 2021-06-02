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

#ifndef OS_DIR_H
#define OS_DIR_H

#include <stddef.h>

/**
 * @file os_dir.h
 *
 * @brief Directory-related OS functions.
 */

/**
 * @brief Create a directory to the specified path.
 *
 * The creation of the directory can be recursive. The slashes are automatically converted to the
 * OS native ones.
 *
 * @return 0 if the folder was successfully created (or already existed),
 * a non-zero value if an error occured
 */
int OAL_create_directory(const char *path);

#endif
