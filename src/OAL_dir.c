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
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "OAL_dir.h"
#include "OAL_file.h"
#include "OAL_paths.h"
#include "OAL_string.h"
#include "private_funcs.h"

#if defined(OAL_IS_POSIX)
#include <unistd.h>

#elif OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <direct.h>

#define getcwd _getcwd
#define mkdir(x, y) _mkdir(x)
#endif

static int OAL_create_non_recursive_dir(const char *path)
{
	if(!path) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return -1;
	/* Check if folder exists to not catch "file already exists"-like errors */
	} else if(OAL_file_exists(path) != 0) {
		if(mkdir(path, 0777) == 0) return 0;
		else if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);

		return -1;
	} else return 0;
}

int OAL_create_dir(const char *path)
{
	if(!path) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return -1;
	}

	for(size_t i = 0; i < strlen(path); ++i) {
		if(i == strlen(path) - 1) {
			if(OAL_file_exists(path) != 0) {
				char *current_directory;
				int rtrn_val;

				if(!(current_directory = malloc((i + 2) * sizeof(char)))) {
					p_set_error(OAL_ERROR_ALLOC_FAILED);
					return -1;
				}
				strncpy(current_directory, path, i + 1);
				current_directory[i + 1] = '\0';
				if(p_is_dir_separator(current_directory[i])) {
					current_directory[i] = '\0';
				}

				rtrn_val = OAL_create_non_recursive_dir(current_directory);
				free(current_directory);

				return rtrn_val;
			}
		} else if(p_is_dir_separator(path[i]) && i != 0) {
			char *current_directory;

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
			/* Detect if this is the part of the path with the drive letter */
			if(path[i-1] == ':') continue;
#endif
			/* Error code set by OAL_strdup */
			current_directory = OAL_strdup(path);
			if(!current_directory) return -1;
			current_directory[i] = '\0';

			if(OAL_file_exists(current_directory) != 0) {
				/* Error code set by OAL_create_non_recursive_dir */
				if(OAL_create_non_recursive_dir(current_directory) != 0) {
					free(current_directory);
					return -1;
				}
			}
			free(current_directory);
		}
	}
	return 0;
}
