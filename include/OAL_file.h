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

#include <stdio.h>

/**
 * @file OAL_file.h
 *
 * @brief File-related OS functions.
 */

/**
 * @brief Check if a file (including directories) exists.
 *
 * @param path The path to the file to check
 *
 * @return 0 if the file exists,
 * a non-zero value if an error occured or if the file does not exists (check
 * the error code for more information).
 */
int OAL_file_exists(const char *path);

/**
 * @brief Check if a path points to a regular file.
 *
 * A regular file is a text or a binary file. Examples of files that are not
 * "regular" are directories and symbolic links.
 *
 * @param path The path to the file to check
 *
 * @return 0 if the file exists,
 * a non-zero value if an error occured or if the file is not regular (check
 * the error code for more information).
 */
int OAL_is_file_regular(const char *path);

/**
 * @brief Return a file pointer to the specified file
 *
 * If not equal to NULL, the FILE pointer must be passed to fclose when it is
 * not needed anymore. Any standard C function can use the returned FILE
 * pointer.
 *
 * @param path The path pointing to the file to open
 * @param mode The fopen mode
 *
 * @return a FILE pointer to the specified file path if no error occured,
 * else NULL.
 */
FILE *OAL_fopen(const char *path, const char *mode);

/**
 * @brief Remove the file pointed by the path
 *
 * @param path The path pointing to the file to remove
 *
 * @return 0 if the function succeeds,
 * -1 if an error occured.
 */
int OAL_remove_file(const char *path);
#endif
