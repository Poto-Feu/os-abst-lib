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

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <fileapi.h>

#include "OAL_file.h"
#include "private_funcs.h"
#include "win_nt/private_funcs_win_nt.h"

int OAL_file_exists(const char *path)
{
	DWORD attribs;
	wchar_t *path_w = NULL;
	int return_val = -1;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) goto error_exit;

	if((attribs = GetFileAttributesW(path_w)) != INVALID_FILE_ATTRIBUTES) {
		return_val = 0;
	} else {
		p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		goto error_exit;
	}
error_exit:
	free(path_w);
	return return_val;
}
#endif
