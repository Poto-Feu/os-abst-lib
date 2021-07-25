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

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "OAL_paths.h"
#include "private_funcs.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <direct.h>

#define getcwd _getcwd
#endif

/* OAL_get_max_filepath_len never fails for now. However, if the implementation
 * changes in the future, it will set its own error code. */

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD \
				   || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
long OAL_get_executable_dir(char *buffer, long size)
{
	char *exec_path = NULL;
	long final_slash_pos = -1;
	long min_buf_size;
	long exec_path_len;
	long i;
	long rtrn_val = -1;
	bool is_NUL_encountered = false;
	
	if((exec_path_len = OAL_get_executable_path(NULL, 0)) == -1) {
		goto error_exit;
	} else if(!(exec_path = malloc(exec_path_len))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		goto error_exit;
	} else if(OAL_get_executable_path(exec_path, exec_path_len) != 0) {
		goto error_exit;
	}

	/* We search the last slash of the path to find the length of the part of
	 * the strings that will be copied. */
	for(i = 0; i < exec_path_len && !is_NUL_encountered; ++i) {
		if(p_is_dir_separator(exec_path[i])) final_slash_pos = i;
		else if(exec_path[i] == '\0') is_NUL_encountered = true;
	}

	min_buf_size = final_slash_pos + 2;
	if(min_buf_size > size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		rtrn_val = min_buf_size;
		goto error_exit;
	}

	exec_path[final_slash_pos] = OS_DIR_SEPARATOR;
	exec_path[final_slash_pos + 1] = '\0';
	strcpy(buffer, exec_path);
	
	rtrn_val = 0;
error_exit:
	free(exec_path);
	return rtrn_val;
}
#else
#warning "OAL executable path functions are not available on your system"
#endif
