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

#ifndef OS_PATHS_H
#define OS_PATHS_H

#include "OAL_os.h"

/**
 * @file OAL_paths.h
 *
 * @brief Paths-related OS functions.
 *
 * If the specified buffer size is too small, the buffer is untouched and
 * the minimal required size is returned. This means that a NULL pointer can
 * be passed as buffer and 0 as value to get the required size of the buffer.
 *
 * If there is any copying, the returned path will be null-terminated.
 *
 * If size value is negative, the behavior is undefined.
 *
 * Note that the behavior of these functions are similar to strncpy: if the
 * block pointed by buffer is shorter than the specified size, the behavior is
 * undefined.
 */

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD \
				   || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
/**
 * @brief Return the path of the running executable.
 * 
 * @param buffer string pointer in which the path should be copied
 * @param size size of the buffer
 *
 * @return 0 if the string was successfully copied,
 * the required size if the specified buffer size is too small,
 * -1 if an error occured
 */
long OAL_get_executable_path(char *buffer, long size);

/**
 * @brief Return the path of the directory containing the running executable.
 * 
 * @param buffer string pointer in which the path should be copied
 * @param size size of the buffer
 *
 * @return 0 if the string was successfully copied,
 * the required size if the specified buffer size is too small,
 * -1 if an error occured
 */
long OAL_get_executable_dir(char *buffer, long size);
#endif

/**
 * @brief Return the path of the current working directory.
 * 
 * @param buffer string pointer in which the path should be copied
 * @param size size of the buffer
 *
 * @return 0 if the string was successfully copied,
 * the required size if the specified buffer size is too small,
 * -1 if an error occured
 */
long OAL_get_working_dir(char *buffer, long size);

/**
 * @brief Copy the user data directory path into a buffer.
 *
 * In most OSes, there is a convention on where programs should store their
 * user-specific data. The library does not return the path to a subdirectory
 * specifically created for the current executable - this decision is up to the
 * programmer.
 *
 * @return 0 if the string was successfully copied,
 * the required size if the specified buffer size is too small,
 * -1 if an error occured
 */
long OAL_get_user_data_dir(char *buffer, long size);

/**
 * @brief Return the maximum length of file paths on the running OS.
 *
 * This function cannot fail on any supported OS. However, a future
 * implementation may "fail" hence the return error value.
 *
 * @return The maximum file path length if successful,
 * -1 if an error occured.
 */
long OAL_get_max_filepath_len(void);
#endif
