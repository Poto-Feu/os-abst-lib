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
#include <errno.h>

#include <errhandlingapi.h>
#include <fcntl.h>
#include <fileapi.h>
#include <handleapi.h>
#include <winerror.h>

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

FILE *OAL_open_file(const char *path, const char *mode)
{
	wchar_t *path_w = NULL;
	wchar_t *mode_w = NULL;
	FILE *stream = NULL;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) goto error_exit;
	else if(!(mode_w = p_utf8_to_alloc_utf16(mode))) goto error_exit;
	else if(!(stream = _wfopen(path_w, mode_w))) {
		p_set_fopen_error();
		goto error_exit;
	}

error_exit:
	free(path_w);
	free(mode_w);
	return stream;
}

int OAL_remove_file(const char *path)
{
	int return_val;
	wchar_t *path_w = NULL;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) return -1;
	else if((return_val = _wremove(path_w)) == -1) {
		if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
		else if(errno == ENOENT) p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);
	}

	free(path_w);
	return return_val;
}
#endif
