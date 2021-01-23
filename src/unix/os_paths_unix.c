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

#include "private_consts.h"

#if defined(OAL_IS_POSIX)

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_paths.h"
#include "os_dir.h"

#if OAL_TARGET_OS == OAL_OS_FREEBSD

#include <sys/types.h>
#include <sys/sysctl.h>

#endif

const char *const user_data_dir_suffix = "/.local/share/";

int OAL_get_USER_DATA_PATH(char *buffer, size_t size)
{
	const char *HOME_env = getenv("HOME");
	size_t path_len = OAL_get_USER_DATA_PATH_length();

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(!HOME_env || path_len == 0) return -1;
	else if(size < path_len) return -1;

	strcpy(buffer, HOME_env);
	strcat(buffer, user_data_dir_suffix);
	buffer[path_len - 1] = '\0';

	return 0;
}

size_t OAL_get_USER_DATA_PATH_length(void)
{
	const char *HOME_env = getenv("HOME");

	if(!HOME_env) return 0;
	else return strlen(HOME_env) + strlen(user_data_dir_suffix) + 1; /* Add 1 character for the
																		null terminator */
}

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD
int OAL_get_executable_path(char *buffer, size_t size)
{
	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0) {
		errno = EINVAL;
		return -1;
	}

	/* This is a tricky part since each POSIX OS has its own way of fetching the path of the
	 * currently running executable. Hence this function must be manually ported. */
#if OAL_TARGET_OS == OAL_OS_GNU_LINUX
	ssize_t readlink_rtrn = readlink("/proc/self/exe", buffer, size);

	if(readlink_rtrn != -1 && (size_t)readlink_rtrn != size && (size_t)readlink_rtrn < size) {
		buffer[readlink_rtrn] = '\0';
		return 0;
	} else return -1;

#elif OAL_TARGET_OS == OAL_OS_FREEBSD
	int mib[4];

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PATHNAME;
	mib[3] = -1;

	--size;

	if(sysctl(mib, 4, buffer, &size, NULL, 0) == 0) {
		buffer[size] = '\0';
		return 0;
	} else return -1;
#endif
}

#else
#warning "OAL_get_executable_path is not available on your system"
#endif

size_t OAL_get_max_filepath_length(void)
{
	ssize_t pathconf_rtrn = pathconf("/", _PC_PATH_MAX);

	if(pathconf_rtrn < 0) return 0;
	return (size_t)pathconf_rtrn;
}

#endif
