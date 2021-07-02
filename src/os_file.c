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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "os_file.h"
#include "os_paths.h"
#include "os_string.h"
#include "private_funcs.h"
#include "private_consts.h"

int OAL_file_exists(const char *path)
{
#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	struct _stat buf;
#else
	struct stat buf;
#endif
	int rtrn_val;

	if(!path) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return -1;
	}

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	rtrn_val = _stat(path, &buf);
#else
	rtrn_val = stat(path, &buf);
#endif
	if(rtrn_val != 0) p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
	return rtrn_val;
}

int OAL_remove_file(const char *path)
{
	if(!path) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return -1;
	} else if(remove(path) != 0) {
		if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		return -1;
	} else return 0;
}
