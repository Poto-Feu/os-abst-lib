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
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include <errhandlingapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <minwinbase.h>
#include <winerror.h>

#include "OAL_dir.h"
#include "OAL_file.h"
#include "private_funcs.h"
#include "win_nt/private_funcs_win_nt.h"

int p_create_non_recursive_dir(const char *path)
{
	wchar_t *path_w;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) return -1;
	else if(!CreateDirectoryW(path_w, NULL)) {
		DWORD err = GetLastError();

		free(path_w);
		if(err == ERROR_ALREADY_EXISTS) return 0;
		else return -1;
	} else {
		free(path_w);
		return 0;
	}
}

long OAL_get_dir_file_count(const char *dir)
{
	WIN32_FIND_DATAW file_data;
	HANDLE file_handle;
	char *first_file_str;
	wchar_t *first_file_wstr;
	long count = 0;

	if(OAL_file_exists(dir) != 0) {
		p_set_error(OAL_ERROR_FILE_NOT_EXISTS);
		return -1;
	} else if(!(first_file_str = malloc((strlen(dir) + 3) * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return -1;
	}
	strcpy(first_file_str, dir);
	strcat(first_file_str, "\\*");

	if(!(first_file_wstr = p_utf8_to_alloc_utf16(first_file_str))) {
		free(first_file_str);
		return -1;
	}
	free(first_file_str);

	if((file_handle = FindFirstFileW(first_file_wstr, &file_data))
			== INVALID_HANDLE_VALUE) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		free(first_file_str);
		free(first_file_wstr);
		return -1;
	}
	free(first_file_wstr);

	while(FindNextFileW(file_handle, &file_data) != FALSE
			&& count != LONG_MAX) {
		if(wcscmp(file_data.cFileName, L"..") != 0 &&
				wcscmp(file_data.cFileName, L".") != 0
				&& !(file_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
			++count;
		}
	}

	FindClose(file_handle);

	return count;
}
#endif
