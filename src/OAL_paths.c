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
long OAL_get_executable_path_len(void)
{
	long max_filepath_length = OAL_get_max_filepath_len();
	char *exec_path;

	if(max_filepath_length == -1) return -1;
	else if(!(exec_path = malloc(max_filepath_length * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return -1;
	}

	/* Sets its own error code */
	if(OAL_get_executable_path(exec_path, max_filepath_length) == 0) {
		size_t path_length = strlen(exec_path);

		free(exec_path);
		return path_length + 1;
	} else {
		free(exec_path);
		return -1;
	}
}

long OAL_get_executable_dir(char *buffer, size_t size)
{
	char *exec_path = NULL;
	long final_slash_pos = -1;
	long exec_path_length = OAL_get_max_filepath_len();
	long i;
	long return_val = -1;
	bool is_NUL_encountered = false;
	
	if(size == 0 || size == 1) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		goto error_exit;
	} else if(exec_path_length == -1) goto error_exit;
	else if(!(exec_path = malloc(exec_path_length))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		goto error_exit;
	} else if(OAL_get_executable_path(exec_path, exec_path_length) != 0) {
		goto error_exit;
	}

	/* We search the last slash of the path to find the length of the part of
	 * the strings that will be copied. */
	for(i = 0; i < exec_path_length && !is_NUL_encountered; ++i) {
		if(p_is_dir_separator(exec_path[i])) final_slash_pos = i;
		else if(exec_path[i] == '\0') is_NUL_encountered = true;
	}

	if(final_slash_pos == -1 || (size_t)final_slash_pos > size - 2) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		goto error_exit;
	}

	exec_path[final_slash_pos] = OS_DIR_SEPARATOR;
	exec_path[final_slash_pos + 1] = '\0';
	strcpy(buffer, exec_path);
	
	return_val = 0;
error_exit:
	free(exec_path);
	return return_val;
}

long OAL_get_executable_dir_len(void)
{
	long max_filepath_length = OAL_get_max_filepath_len();
	char *exec_dir;

	if(max_filepath_length == -1) return -1;
	else if(!(exec_dir = malloc(max_filepath_length * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return -1;
	} else if(OAL_get_executable_dir(exec_dir, max_filepath_length) == 0) {
		size_t path_length = strlen(exec_dir);

		free(exec_dir);
		return path_length + 1;
	} else {
		free(exec_dir);
		return -1;
	}
}
#else
#warning "OAL executable path functions are not available on your system"
#endif

long OAL_get_working_dir_len(void)
{
	long max_filepath_length = OAL_get_max_filepath_len();
	char *working_dir;

	if(max_filepath_length == -1) return -1;
	else if(!(working_dir = malloc(max_filepath_length * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return -1;
	}

	if(OAL_get_working_dir(working_dir, max_filepath_length) == 0) {
		long working_dir_len = strlen(working_dir);

		free(working_dir);
		return working_dir_len + 1;
	} else {
		free(working_dir);
		return -1;
	}
}
