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

#ifdef OAL_IS_POSIX
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>

#include "OAL_file.h"
#include "private_funcs.h"

int OAL_file_exists(const char *path)
{
	if(access(path, F_OK) == 0) return 0;
	else {
		p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		return -1;
	}
}

int OAL_is_file_regular(const char *path)
{
	struct stat buf;

	if(stat(path, &buf) != 0) {
		p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		return -1;
	} else if(!S_ISREG(buf.st_mode)) {
		p_set_error(OAL_ERROR_FILE_NOT_REGULAR);
		return -1;
	} else return 0;
}
#endif
