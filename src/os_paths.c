/*
    Copyright (C) 2021 Adrien Saad

    This file is part of OsAbstLibrary.

    OsAbstLibrary is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OsAbstLibrary is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OsAbstLibrary. If not, see <https://www.gnu.org/licenses/>.
*/

#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_paths.h"
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <direct.h>

#define getcwd _getcwd

#endif

void OAL_replace_dir_separator_to_native(char *path)
{
	for(size_t i = 0; path[i] != '\0'; ++i) {
		if(path[i] == OTHER_OS_DIR_SEPARATOR) {
			path[i] = OS_DIR_SEPARATOR;
		}
	}
}

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
	
	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	} else if(OAL_get_executable_path(buffer, size) != 0) return -1;

	for(size_t i = 0; i < size && buffer[i] != '\0'; ++i) {
		if(buffer[i] == OS_DIR_SEPARATOR) final_slash_pos = i;
	}

	if(final_slash_pos == -1) return -1;
	else {
		buffer[final_slash_pos] = OS_DIR_SEPARATOR;
		buffer[final_slash_pos + 1] = '\0';
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

		if(buffer[path_len - 1] != OS_DIR_SEPARATOR) {
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
