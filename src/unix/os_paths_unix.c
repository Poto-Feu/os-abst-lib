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

#if defined(OAL_IS_POSIX)

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_paths.h"
#include "os_dir.h"
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_FREEBSD

#include <sys/types.h>
#include <sys/sysctl.h>

#endif

const char *const user_data_dir_suffix = "/.local/share/";

/* The XDG Base Directory Specs specifies that $HOME/.local/share should be used if the
 * XDG_DATA_HOME environment variable is not set. */
static int OAL_get_user_data_dir_no_env(char *buffer, size_t size)
{
	const char *HOME_env = getenv("HOME");
	size_t path_len;

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(!HOME_env) return -1;

	path_len = strlen(HOME_env) + strlen(user_data_dir_suffix);
	if(size < path_len + 1) {
		errno = EFAULT;
		return -1;
	}

	strcpy(buffer, HOME_env);
	strcat(buffer, user_data_dir_suffix);
	buffer[path_len] = '\0';

	return 0;
}

int OAL_get_user_data_dir(char *buffer, size_t size)
{
	const char *XDG_DATA_HOME_env = getenv("XDG_DATA_HOME");

	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(XDG_DATA_HOME_env) {
		strncpy(buffer, XDG_DATA_HOME_env, size);
		if(buffer[size - 1] != '\0' || buffer[size - 2] != '\0') return -1;

		buffer[strlen(buffer)] = OS_DIR_SEPARATOR;
		return 0;
	} else return OAL_get_user_data_dir_no_env(buffer, size);
}

size_t OAL_get_user_data_dir_len(void)
{
	const char *XDG_DATA_HOME_env = getenv("XDG_DATA_HOME");

	if(XDG_DATA_HOME_env) {
		/* 1 char for the slash separator and 1 char for the NULL terminator */
		return strlen(XDG_DATA_HOME_env) + 2;
	} else {
		const char *HOME_env = getenv("HOME");

		/* Add 1 character for the null terminator */
		if(!HOME_env) return 0;
		else return strlen(HOME_env) + strlen(user_data_dir_suffix) + 1; 
	}
}

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD
int OAL_get_executable_path(char *buffer, size_t size)
{
	if(!buffer) {
		errno = EFAULT;
		return -1;
	} else if(size == 0 || size == 1) {
		errno = EINVAL;
		return -1;
	}

	/* This is a tricky part since each POSIX OS has its own way of fetching the path of the
	 * currently running executable. Hence this function must be manually ported. */
#if OAL_TARGET_OS == OAL_OS_GNU_LINUX
	ssize_t readlink_rtrn = readlink("/proc/self/exe", buffer, size);

	if(readlink_rtrn != -1 && (size_t)readlink_rtrn < size) {
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

size_t OAL_get_max_filepath_len(void)
{
	ssize_t pathconf_rtrn = pathconf("/", _PC_PATH_MAX);

	if(pathconf_rtrn < 0) return 0;
	return (size_t)pathconf_rtrn;
}
#endif
