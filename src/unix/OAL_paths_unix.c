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

#include "OAL_os.h"

#if defined(OAL_IS_POSIX)

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include "OAL_paths.h"
#include "OAL_dir.h"
#include "private_funcs.h"

#if OAL_TARGET_OS == OAL_OS_FREEBSD

#include <sys/sysctl.h>

#endif

const char *const user_data_dir_suffix = "/.local/share/";

char *get_max_fp_len_block(long *path_len)
{
	char *block = NULL;
	long max_fp_len;

	if((max_fp_len = OAL_get_max_filepath_len()) == -1) return NULL;
	else if(!(block = malloc(max_fp_len * sizeof(char)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return NULL;
	} else if(path_len) *path_len = max_fp_len;
	return block;
}

/* The XDG Base Directory Specs specifies that $HOME/.local/share should be
 * used if the XDG_DATA_HOME environment variable is not set. */
static long OAL_get_user_data_dir_no_env(char *buffer, long size)
{
	const char *HOME_env = getenv("HOME");
	long min_buf_size;

	if(!HOME_env) {
		p_set_error(OAL_ERROR_MISSING_ENV);
		return -1;
	}

	min_buf_size = strlen(HOME_env) + strlen(user_data_dir_suffix) + 1;
	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		return min_buf_size;
	}

	strcpy(buffer, HOME_env);
	strcat(buffer, user_data_dir_suffix);

	return 0;
}

long OAL_get_user_data_dir(char *buffer, long size)
{
	const char *XDG_DATA_HOME_env = getenv("XDG_DATA_HOME");

	if(XDG_DATA_HOME_env) {
		long min_buf_size = strlen(XDG_DATA_HOME_env) + 2;

		if(size < min_buf_size) {
			p_set_error(OAL_ERROR_BUFFER_SIZE);
			return min_buf_size;
		}
		strcpy(buffer, XDG_DATA_HOME_env);

		buffer[strlen(buffer)] = OS_DIR_SEPARATOR;
		return 0;
	} else return OAL_get_user_data_dir_no_env(buffer, size);
}

#if OAL_TARGET_OS == OAL_OS_GNU_LINUX || OAL_TARGET_OS == OAL_OS_FREEBSD
long OAL_get_executable_path(char *buffer, long size)
{
	/* This is a tricky part since each POSIX OS has its own way of fetching
	 * the path of the currently running executable. Hence this function must
	 * be manually ported. */
#if OAL_TARGET_OS == OAL_OS_GNU_LINUX
	ssize_t readlink_rtrn;
#elif OAL_TARGET_OS == OAL_OS_FREEBSD
	int mib[4];
	size_t max_fp_len_st;
#endif
	char *tmp_buf = NULL;
	long min_buf_size;
	long max_fp_len;

	if(!(tmp_buf = get_max_fp_len_block(&max_fp_len))) return -1;
#if OAL_TARGET_OS == OAL_OS_GNU_LINUX
	readlink_rtrn = readlink("/proc/self/exe", tmp_buf, max_fp_len);
	if(readlink_rtrn == -1) {
		if(errno == EACCES) p_set_error(OAL_ERROR_FILE_PERMS);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		free(tmp_buf);
		return -1;
	}

	min_buf_size = readlink_rtrn + 1;
	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		free(tmp_buf);
		return min_buf_size;
	}
	tmp_buf[readlink_rtrn] = '\0';
#elif OAL_TARGET_OS == OAL_OS_FREEBSD
	max_fp_len_st = (size_t)max_fp_len;
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PATHNAME;
	mib[3] = -1;

	if(sysctl(mib, 4, tmp_buf, &max_fp_len_st, NULL, 0) != 0) {
		if(errno == EACCES || errno == EPERM) {
			p_set_error(OAL_ERROR_FILE_PERMS);
			free(tmp_buf);
			return -1;
		} else {
			p_set_error(OAL_ERROR_UNKNOWN_ERROR);
			free(tmp_buf);
			return -1;
		}
	}
	tmp_buf[max_fp_len_st - 1] = '\0';

	min_buf_size = strlen(tmp_buf) + 1;
	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		free(tmp_buf);
		return min_buf_size;
	}
#endif
	strcpy(buffer, tmp_buf);
	free(tmp_buf);
	return 0;
}
#else
#warning "OAL_get_executable_path is not available on your system"
#endif

long OAL_get_working_dir(char *buffer, long size)
{
	long max_fp_len;
	long min_buf_size;
	char *tmp_buf;

	if(!(tmp_buf = get_max_fp_len_block(&max_fp_len))) return -1;
	else if(!getcwd(tmp_buf, max_fp_len)) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		free(tmp_buf);
		return -1;
	}

	min_buf_size = strlen(tmp_buf) + 2;
	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		free(tmp_buf);
		return min_buf_size;
	}

	strcpy(buffer, tmp_buf);

	if(!p_is_dir_separator(buffer[strlen(buffer) - 1])) {
		buffer[min_buf_size - 2] = OS_DIR_SEPARATOR;
		buffer[min_buf_size - 1] = '\0';
	}
	free(tmp_buf);

	return 0;
}

long OAL_get_max_filepath_len(void)
{
	/* There is no reason for this function to fail with these args. */
	return pathconf("/", _PC_PATH_MAX);
}
#endif
