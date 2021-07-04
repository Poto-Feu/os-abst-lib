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

#include "OAL_os.h"

#define WINDOWS_DIR_SEPARATOR '\\'
#define UNIX_DIR_SEPARATOR '/'

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#define OS_DIR_SEPARATOR WINDOWS_DIR_SEPARATOR
#else
#define OS_DIR_SEPARATOR UNIX_DIR_SEPARATOR
#endif

extern const unsigned int false;
extern const unsigned int true;

typedef unsigned int bool;

#endif
