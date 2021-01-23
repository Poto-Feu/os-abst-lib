/*
    Copyright (C) 2021 Adrien Saad

    This file is part of OsAbstLibrary.

    SwannSong Adventure is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SwannSong Adventure is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with SwannSong Adventure.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "os_type.h"
#include "private_consts.h"

os_type_t OAL_get_os_type(void)
{
#if OAL_TARGET_OS == OAL_OS_LINUX
	return OS_TYPE_GNU_LINUX;
#elif OAL_TARGET_OS == OAL_OS_FREEBSD
	return OS_TYPE_FREEBSD;
#elif OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	return OS_TYPE_WINDOWS_NT;
#else
	return OS_TYPE_OTHER;
#endif
}

int OAL_is_os_posix(void)
{
#if defined(OAL_IS_POSIX)
	return 0;
#else
	return -1;
#endif
}
