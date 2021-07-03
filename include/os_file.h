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

#ifndef OS_FILE_H
#define OS_FILE_H

/**
 * @file os_file.h
 *
 * @brief File-related OS functions.
 */

/**
 * @brief Check if a file (including directories) exists.
 *
 * @param path The path to the file to check
 * @return 0 if the file exists,
 * a non-zero value if an error occured or if the file does not exists (check
 * the error code for more information).
 */
int OAL_file_exists(const char *path);
#endif
