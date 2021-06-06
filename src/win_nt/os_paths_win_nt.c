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

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <libloaderapi.h>

#include "os_paths.h"
#include "os_dir.h"
#include "private_consts.h"

int OAL_get_user_data_path(char *buffer, size_t size)
{
	const char *LOCALAPPDATA_env = getenv("LOCALAPPDATA");

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	} else if(!LOCALAPPDATA_env) return -1;

	strncpy(buffer, LOCALAPPDATA_env, size);
	if(buffer[size - 1] != '\0' || buffer[size - 2] != '\0') return -1;

	buffer[strlen(buffer)] = OS_DIR_SEPARATOR;
	return 0;
}

size_t OAL_get_user_data_path_length(void)
{
	const char *LOCALAPPDATA_env = getenv("LOCALAPPDATA");

	/* Add 2 characters for the end slash and the null terminator */
	if(!LOCALAPPDATA_env) return 0;
	else return strlen(LOCALAPPDATA_env) + 2; 
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

	/* If GetModuleFileNameA fails, it returns 0. If the buffer is too small, it returns the
	 * specified size. However, if the path is fully copied into the buffer, the function returns
	 * the path length minus the NUL terminator. With a buffer large enough to contain the NUL
	 * terminator, it will not return "size". */
	path_end_index = GetModuleFileNameA(NULL, buffer, size);
	if(path_end_index != 0 && path_end_index != size) return 0;
	else return -1;
}

size_t OAL_get_max_filepath_length(void)
{
	/* Long file paths are not supported - not a big deal since they are not enabled by default. */
	return 260; 
}

#endif
