/*
    Copyright (C) 2021 Adrien Saad

    This file is part of OsAbstLibrary.

    OsAbstLibrary is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OsAbstLibrary is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OsAbstLibrary. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef OS_PATHS_H
#define OS_PATHS_H

#include <stddef.h>

/*!
 * \file os_paths.h
 *
 * \brief Paths-related OS functions.
 */

/*!
 * \brief Replace path directory separators with native ones.
 * 
 * \param path path where the separators should be replaced
 */
void OAL_replace_dir_separator_to_native(char *path);

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD \
				   || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
/*!
 * \brief Return the path of the running executable.
 * 
 * \param buffer string pointer in which the path should be copied
 * \param size size of the buffer
 *
 * \return 0 if the string was successfully copied
 * a non-zero value if an error occured
 */
int OAL_get_executable_path(char *buffer, size_t size);

/*!
 * \brief Return the executable path length (including the null terminator).
 *
 * \return The path length if successful,
 * 0 if an error occured.
 */
size_t OAL_get_executable_path_length(void);

/*!
 * \brief Return the path of the directory containing the running executable.
 * 
 * \param buffer string pointer in which the path should be copied
 * \param size size of the buffer
 *
 * \return 0 if the string was successfully copied
 * a non-zero value if an error occured
 */
int OAL_get_executable_directory(char *buffer, size_t size);

/*!
 * \brief Return the executable directory path length (including the null terminator)
 *
 * \return The path length if successful,
 * 0 if an error occured.
 */
size_t OAL_get_executable_directory_length(void);

#endif

/*!
 * \brief Return the path of the current working directory.
 * 
 * \param buffer string pointer in which the path should be copied
 * \param size size of the buffer
 *
 * \return 0 if the string was successfully copied
 * a non-zero value if an error occured
 */
int OAL_get_working_directory(char *buffer, size_t size);

/*!
 * \brief Return the user working directory path length (including the null terminator)
 *
 * \return The path length if there was no error,
 * 0 if an error occured.
 */
size_t OAL_get_working_directory_length(void);

/*!
 * \brief Return the maximum length of file paths on the running OS.
 *
 * \return The maximum file path length if successful,
 * 0 if an error occured.
 */
size_t OAL_get_max_filepath_length(void);

/*!
 * \brief Copy the user data path into a buffer.
 *
 * \return 0 if the string was successfully copied,
 * a non-zero value if an error occured.
 */
int OAL_get_USER_DATA_PATH(char *buffer, size_t size);

/*!
 * \brief Return the user data path length (including the null terminator)
 *
 * \return The path length if successful,
 * 0 if an error occured.
 */
size_t OAL_get_USER_DATA_PATH_length(void);

#endif
