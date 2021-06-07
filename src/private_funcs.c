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

#include "private_funcs.h"
#include "private_consts.h"

bool OAL_is_dir_separator(char ch)
{
#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	return (ch == WINDOWS_DIR_SEPARATOR || ch == POSIX_DIR_SEPARATOR);
#else
	return (ch == POSIX_DIR_SEPARATOR);
#endif
}
