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
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_paths.h"
#include "private_funcs.h"
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <direct.h>

#define getcwd _getcwd
#endif

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD \
				   || OAL_TARGET_OS == OAL_OS_WINDOWS_NT
size_t OAL_get_executable_path_length(void)
{
	size_t max_filepath_length = OAL_get_max_filepath_length();
	char *exec_path;

	if(max_filepath_length == 0) return 0;
	exec_path = malloc(max_filepath_length * sizeof(char));
	if(!exec_path) return 0;

	if(OAL_get_executable_path(exec_path, max_filepath_length) == 0) {
		size_t path_length = strlen(exec_path);

		free(exec_path);
		return path_length + 1;
	} else {
		free(exec_path);
		return 0;
	}
}

int OAL_get_executable_directory(char *buffer, size_t size)
{
	ssize_t final_slash_pos = -1;
	size_t exec_path_length = OAL_get_max_filepath_length();
	char *exec_path;
	bool is_NUL_encountered = false;
	
	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	} else if(exec_path_length == 0) return -1;

	exec_path = malloc(exec_path_length);
	if(!exec_path) return -1;
	else if(OAL_get_executable_path(exec_path, exec_path_length) != 0) {
		free(exec_path);
		return -1;
	}

	/* We search the last slash of the path to find the length of the part of the strings that will
	 * be copied. */
	for(size_t i = 0; i < exec_path_length && !is_NUL_encountered; ++i) {
		if(OAL_is_dir_separator(exec_path[i])) final_slash_pos = i;
		else if(exec_path[i] == '\0') is_NUL_encountered = true;
	}

	/* We don't need to care about the side effects of the size_t cast as the only possible negative
	 * value is -1 and it is already taken into account. */
	if(final_slash_pos == -1 || (size_t)final_slash_pos > size - 2) {
		free(exec_path);
		return -1;
	} else {
		exec_path[final_slash_pos] = OS_DIR_SEPARATOR;
		exec_path[final_slash_pos + 1] = '\0';
		strcpy(buffer, exec_path);
		free(exec_path);
		return 0;
	}
}

size_t OAL_get_executable_directory_length(void)
{
	size_t max_filepath_length = OAL_get_max_filepath_length();
	char *exec_dir;

	if(max_filepath_length == 0) return 0;
	exec_dir = malloc(max_filepath_length * sizeof(char));
	if(!exec_dir) return 0;

	if(OAL_get_executable_directory(exec_dir, max_filepath_length) == 0) {
		size_t path_length = strlen(exec_dir);

		free(exec_dir);
		return path_length + 1;
	} else {
		free(exec_dir);
		return 0;
	}
}
#else
#warning "OAL_get_executable_directory is not available on your system"
#endif

int OAL_get_working_directory(char *buffer, size_t size)
{
	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	} else if(getcwd(buffer, size)) {
		size_t path_len = strlen(buffer);

		if(!OAL_is_dir_separator(buffer[path_len - 1])) {
			if(path_len + 1 < size) {
				buffer[path_len] = OS_DIR_SEPARATOR;
				buffer[path_len + 1] = '\0';
			} else return -1;
		}
	} else return -1;
	return 0;
}

size_t OAL_get_working_directory_length(void)
{
	size_t max_filepath_length = OAL_get_max_filepath_length();
	char *working_dir;

	if(max_filepath_length == 0) return 0;
	working_dir = malloc(max_filepath_length * sizeof(char));
	if(!working_dir) return 0;

	if(OAL_get_working_directory(working_dir, max_filepath_length) == 0) {
		size_t path_length = strlen(working_dir);

		free(working_dir);
		return path_length + 1;
	} else {
		free(working_dir);
		return 0;
	}
}
