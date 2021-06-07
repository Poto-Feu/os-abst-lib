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

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "os_file.h"
#include "os_paths.h"
#include "os_string.h"
#include "private_funcs.h"
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#define stat _stat
#endif

int OAL_file_exists(const char *path)
{
#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	struct _stat buf;
#else
	struct stat buf;
#endif
	int rtrn_val;

	if(!path) {
		errno = EFAULT;
		return -1;
	}

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	rtrn_val = _stat(path, &buf);
#else
	rtrn_val = stat(path, &buf);
#endif
	return rtrn_val;
}

int OAL_remove_file(const char *path)
{
	int remove_rtrn;

	if(!path) {
		errno = EFAULT;
		return -1;
	}
	remove_rtrn = remove(path);

	return remove_rtrn;
}
