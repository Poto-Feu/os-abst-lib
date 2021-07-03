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
 * @file OAL_dir.h
 *
 * @brief Directory-related OS functions.
 */

/**
 * @brief Create a directory to the specified path.
 *
 * The creation of the directory can be recursive.
 *
 * @return 0 if the folder was successfully created (or already existed),
 * a non-zero value if an error occured
 */
int OAL_create_dir(const char *path);

/**
 * @brief Get the number of files present in the specified directory.
 *
 * Subdirectories are excluded from the file count.
 *
 * @return the number of files present in the specified directory.
 * -1 if an error occured
 */
size_t OAL_get_dir_file_count(const char *dir);

#endif
