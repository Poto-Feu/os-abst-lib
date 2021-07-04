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

#include "OAL_os.h"

#if defined(OAL_IS_POSIX)
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#include <dirent.h>

#include "OAL_dir.h"
#include "private_funcs.h"

long OAL_get_dir_file_count(const char *dir)
{
	DIR *dir_strm;
	struct dirent *entry;
	long count = 0;

	if(!dir) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return 0;
	}

	if(!(dir_strm = opendir(dir))) {
		if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
		else if(errno == ENOTDIR) p_set_error(OAL_ERROR_NOT_A_DIR);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		return 0;
	}

	while((entry = readdir(dir_strm)) && count != LONG_MAX) {
		if(entry->d_type == DT_REG) ++count;
	}

	return count;
}
#endif
