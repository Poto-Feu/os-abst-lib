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

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <string.h>

#include <windows.h>

#include "os_dir.h"
#include "os_file.h"
#include "private_funcs.h"

size_t OAL_get_dir_file_count(const char *dir)
{
	WIN32_FIND_DATAA file_data;
	HANDLE file_handle;
	char *first_file_str;
	long count = 0;

	if(!dir) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return -1;
	}

	if(OAL_file_exists(dir) != 0) return -1;
	else if(!(first_file_str = malloc((strlen(dir) + 3) * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return -1;
	}

	strcpy(first_file_str, dir);
	strcat(first_file_str, "\\*");

	if((file_handle = FindFirstFileA(first_file_str, &file_data))
			== INVALID_HANDLE_VALUE) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		free(first_file_str);
		return -1;
	}
	free(first_file_str);

	while(FindNextFileA(file_handle, &file_data) != FALSE) {
		if(!(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) ++count;
	}

	FindClose(file_handle);

	return count;
}
#endif
