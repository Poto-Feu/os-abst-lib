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

static bool get_file_attribs(const char *path, DWORD *attribs)
{
	wchar_t *path_w = NULL;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) return false;

	*attribs = GetFileAttributesW(path_w);
	free(path_w);

	return true;
}

int OAL_file_exists(const char *path)
{
	DWORD attribs;

	if(!get_file_attribs(path, &attribs)) return -1;
	else if(attribs != INVALID_FILE_ATTRIBUTES) return 0;
	else {
		p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		return -1;
	}
}

int OAL_is_file_regular(const char *path)
{
	DWORD attribs;

	if(!get_file_attribs(path, &attribs)) return -1;
	else if((attribs & FILE_ATTRIBUTE_DIRECTORY)
			|| (attribs & FILE_ATTRIBUTE_REPARSE_POINT)
			|| (attribs & FILE_ATTRIBUTE_TEMPORARY)) {
		p_set_error(OAL_ERROR_FILE_NOT_REGULAR);
		return -1;
	} else return 0;
	
}
#endif
