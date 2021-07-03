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

#ifndef OS_TYPE_H
#define OS_TYPE_H

/**
 * @file OAL_os.h
 *
 * @brief Header containing various members related to OS types.
 */

/**
 * @brief GNU/Linux value for OAL_TARGET_OS.
 */
#define OAL_OS_GNU_LINUX 1
/**
 * @brief FreeBSD value for OAL_TARGET_OS.
 */
#define OAL_OS_FREEBSD 2
/**
 * @brief Windows NT value for OAL_TARGET_OS.
 */
#define OAL_OS_WINDOWS_NT 3
/**
 * @brief Value corresponding to an unknown OS for OAL_TARGET_OS.
 */
#define OAL_OS_OTHER 4

/**
 * @brief Denotes wether the user OS is POSIX.
 *
 * If it is not defined, the user OS is not POSIX.
 */
#define OAL_IS_POSIX 1

/* Simplify the discrepancies between how different OSes of the same type
 * define their macros.*/
#if !defined(unix) && !defined(__unix__) && !defined(__unix)
#undef OAL_IS_POSIX
#endif

#if defined(__gnu_linux__)
#define OAL_TARGET_OS OAL_OS_GNU_LINUX
#elif defined(__FreeBSD__)
#define OAL_TARGET_OS OAL_OS_FREEBSD
#elif defined(_WIN32)
#define OAL_TARGET_OS OAL_OS_WINDOWS_NT
#else

/**
 * @brief Macro indicating which OS the user is currently using.
 *
 * @sa OAL_get_os_type(void)
 */
#define OAL_TARGET_OS OAL_OS_OTHER
#warning "Target OS not supported"
#endif

/**
 * @brief Enum values corresponding to various OSes.
 *
 * These can be fetch with the OAL_get_os_type(void) function.
 */
enum OAL_os_type {
	OAL_OS_TYPE_GNU_LINUX = OAL_OS_GNU_LINUX,
	OAL_OS_TYPE_FREEBSD = OAL_OS_FREEBSD,
	OAL_OS_TYPE_WINDOWS_NT = OAL_OS_WINDOWS_NT,
	OAL_OS_TYPE_OTHER = OAL_OS_OTHER
};

/**
 * @brief Fetch the user's OS type
 *
 * OAL_TARGET_OS can also be used for compile-time conditions.
 *
 * @return The corresponding OAL_os_type enum value
 *
 * @sa OAL_TARGET_OS
 */
enum OAL_os_type OAL_get_os_type(void);

/**
 * @brief Check wether or not the user's OS is POSIX.
 *
 * @return 0 if the OS is POSIX compatible,
 * a non-zero value if it is not
 */
int OAL_is_os_posix(void);
#endif
