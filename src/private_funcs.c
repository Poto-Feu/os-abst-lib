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

#include "private_funcs.h"

static OAL_error current_error = OAL_ERROR_NO_ERROR;

bool p_is_dir_separator(char ch)
{
#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	return (ch == WINDOWS_DIR_SEPARATOR || ch == UNIX_DIR_SEPARATOR);
#else
	return (ch == UNIX_DIR_SEPARATOR);
#endif
}

void p_set_error(OAL_error error)
{
	current_error = error;
}

OAL_error p_get_current_error(void)
{
	return current_error;
}

void p_set_fopen_error(void)
{
	switch(errno) {
		case ENOENT:
			p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
			break;
		case EINVAL:
			p_set_error(OAL_ERROR_INVALID_MODE);
			break;
		case ENOMEM:
			p_set_error(OAL_ERROR_ALLOC_FAILED);
			break;
		case EACCES:
			p_set_error(OAL_ERROR_FILE_PERMS);
			break;
		default:
			p_set_error(OAL_ERROR_UNKNOWN_ERROR);
			break;
	}
}
