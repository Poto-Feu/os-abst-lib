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

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "os_string.h"
#include "os_type.h"

#if defined(OAL_IS_POSIX) || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include "OAL_flags.h"

extern OAL_FORCEINLINE char *OAL_strdup(const char *src);
#else
char *OAL_strdup(const char *src)
{
	if(!src) {
		errno = EFAULT;
		return NULL;
	}
	char *str;

	str = malloc((strlen(src) + 1) * sizeof(char));
	if(!str) return NULL;

	strcpy(str, src);

	return str;
}
#endif
