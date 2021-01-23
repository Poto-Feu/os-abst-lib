/*
    Copyright (C) 2021 Adrien Saad

    This file is part of OsAbstLibrary.

    OsAbstLibrary is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OsAbstLibrary is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
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
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT

#define stat _stat

#endif

int OAL_file_exists(const char *path)
{
	char *path_dup;
	struct stat buf;
	int rtrn_val;

	if(!path) {
		errno = EFAULT;
		return -1;
	}

	path_dup = OAL_strdup(path);
	if(!path_dup) return -1;
	/* We can't trust the user on directories separators type */
	OAL_replace_dir_separator_to_native(path_dup);
	if(path_dup[strlen(path) - 1] == OS_DIR_SEPARATOR) path_dup[strlen(path) - 1] = '\0';

	rtrn_val = stat(path_dup, &buf);
	free(path_dup);

	return rtrn_val;
}

int OAL_remove_file(const char *path)
{
	char *path_dup;
	int remove_rtrn;

	if(!path) {
		errno = EFAULT;
		return -1;
	}
	path_dup = OAL_strdup(path);
	if(!path_dup) return -1;
	OAL_replace_dir_separator_to_native(path_dup); /* Directories separators... again */

	remove_rtrn = remove(path);
	free(path_dup);

	return remove_rtrn;
}
