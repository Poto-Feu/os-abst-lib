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
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "OAL_dir.h"
#include "private_funcs.h"
#include "OAL_file.h"

int p_create_non_recursive_dir(const char *path)
{
	/* Since mkdir fails if the file already exists and we have checked that
	 * it did not exists before calling this function, race conditions are
	 * mitigated. */
	if(mkdir(path, 0777) == 0) return 0;
	else if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
	else p_set_error(OAL_ERROR_UNKNOWN_ERROR);

	return -1;
}
#endif
