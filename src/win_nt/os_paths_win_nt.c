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

#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <libloaderapi.h>

#include "os_paths.h"
#include "os_dir.h"

int OAL_get_USER_DATA_PATH(char *buffer, size_t size)
{
	const char *APPDATA_env = getenv("APPDATA");
	size_t path_len = OAL_get_USER_DATA_PATH_length();

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(!APPDATA_env || path_len == 0) return -1;
	else if(size < path_len) return -1;

	strcpy(buffer, APPDATA_env);
	buffer[path_len - 2] = OS_DIR_SEPARATOR;
	buffer[path_len - 1] = '\0';
	return 0;
}

size_t OAL_get_USER_DATA_PATH_length(void)
{
	const char *APPDATA_env = getenv("APPDATA");

	/* Add 2 characters for the end slash and the null terminator */
	if(!APPDATA_env) return 0;
	else return strlen(APPDATA_env) + 2; 
}

int OAL_get_executable_path(char *buffer, size_t size)
{
	uint32_t path_end_index;

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	}

	path_end_index = GetModuleFileNameA(NULL, buffer, size);
	if(path_end_index != 0) return 0;
	else return -1;
}

size_t OAL_get_max_filepath_length(void)
{
	/*Long file paths are not supported - not a big deal since they are not enabled by default*/
	return 260; 
				  
}

#endif
