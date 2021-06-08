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

#ifndef OAL_OS_STRING_H
#define OAL_OS_STRING_H

#include <stddef.h>

#include "os_type.h"

#if defined(OAL_IS_POSIX) || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <string.h>
#include "OAL_flags.h"
#endif

/**
 * @file os_string.h
 *
 * @brief String-related functions.
 *
 * This header provides functions that are mostly part of the POSIX specifictation but not the
 * C99 standard. This makes these functions available on systems such as Windows NT.
 */

/**
 * @brief An implementation of the POSIX function strdup.
 *
 * If the program is running on a POSIX OS, the function calls the native strdup.
 * The returned string must be freed to avoid memory leaks.
 * 
 * @param src char pointer to the source string
 *
 * @return a pointer to the duplicated string,
 * NULL if the memory could not be allocated
 */
#if defined(OAL_IS_POSIX) || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
OAL_FORCEINLINE char *OAL_strdup(const char *src)
{
#ifdef OAL_IS_POSIX
	return strdup(src);
#elif OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	return _strdup(src);
#endif
}
#elif
char *OAL_strdup(const char *src);
#endif

#endif
