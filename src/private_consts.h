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

#ifndef PRIVATE_CONSTS_H
#define PRIVATE_CONSTS_H

#define OAL_OS_GNU_LINUX 1
#define OAL_OS_FREEBSD 2
#define OAL_OS_WINDOWS_NT 3
#define OAL_OS_OTHER 4

/*Simplify the discrepancies between how different OSes of the same type defines their macros.*/
#if defined(unix) || defined(__unix__) || defined(__unix)
#define OAL_IS_POSIX 1
#if defined(__gnu_linux__)
#define OAL_TARGET_OS OAL_OS_GNU_LINUX
#elif defined(__FreeBSD__)
#define OAL_TARGET_OS OAL_OS_FREEBSD
#endif

#elif defined(_WIN32)
#define OAL_TARGET_OS OAL_OS_WINDOWS_NT
#else
#define OAL_TARGET_OS OAL_OS_OTHER
#warning "Target OS not supported"
#endif


#define WINDOWS_DIR_SEPERATOR '\\'
#define POSIX_DIR_SEPERATOR '/'

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#define OS_DIR_SEPARATOR WINDOWS_DIR_SEPERATOR
#define OTHER_OS_DIR_SEPARATOR POSIX_DIR_SEPERATOR
#else
#define OS_DIR_SEPARATOR POSIX_DIR_SEPERATOR
#define OTHER_OS_DIR_SEPARATOR WINDOWS_DIR_SEPERATOR
#endif

typedef int hide_iso_warning; /*This typedef removes the empty translation unit warning*/

#endif
