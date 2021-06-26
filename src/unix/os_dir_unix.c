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

#include "os_type.h"

#if defined(OAL_IS_POSIX)
#include <errno.h>
#include <stdlib.h>

#include <dirent.h>

#include "os_dir.h"

size_t OAL_get_dir_file_count(const char *dir)
{
	DIR *dir_strm;
	struct dirent *entry;
	long count = 0;

	if(!dir) {
		errno = EFAULT;
		return -1;
	}

	if(!(dir_strm = opendir(dir))) return -1;

	while((entry = readdir(dir_strm))) {
		if(entry->d_type == DT_REG) ++count;
	}

	return count;
}
#endif
