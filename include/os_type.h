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

/*!
 * \file os_type.h
 *
 * \brief Header containing various members related to OS types.
 */

/*!
 * \brief Values corresponding to various OS.
 */
enum OAL_os_type {
	OAL_OS_TYPE_GNU_LINUX,
	OAL_OS_TYPE_FREEBSD,
	OAL_OS_TYPE_WINDOWS_NT,
	OAL_OS_TYPE_OTHER
};

/*!
 * \brief Fetch the user's OS type
 *
 * \see os_type_t
 * \return The corresponding os_type_t enum value
 */
enum OAL_os_type OAL_get_os_type(void);

/*!
 * \brief Check wether or not the user's OS is POSIX.
 *
 * \return 0 if the OS is POSIX compatible,
 * a non-zero value if it is not
 */
int OAL_is_os_posix(void);

#endif
