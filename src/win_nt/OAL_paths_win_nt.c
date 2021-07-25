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

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <errhandlingapi.h>
#include <libloaderapi.h>
#include <processenv.h>
#include <winerror.h>

#include "OAL_paths.h"
#include "OAL_dir.h"
#include "private_funcs.h"
#include "win_nt/private_funcs_win_nt.h"

static char *get_alloc_env_str(const char *name)
{
	wchar_t *name_w = NULL, *env_w = NULL;
	char *env = NULL;
	DWORD env_w_size = 0;

	if(!(name_w = p_utf8_to_alloc_utf16(name))) goto error_exit;

	env_w_size = GetEnvironmentVariableW(name_w, 0, 0);
	if(!env_w_size) {
		int err = GetLastError();

		if(err == ERROR_ENVVAR_NOT_FOUND) p_set_error(OAL_ERROR_MISSING_ENV);
		else p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		goto error_exit;
	} else if(!(env_w = malloc(env_w_size * sizeof(wchar_t)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		goto error_exit;
	} else if(!(GetEnvironmentVariableW(name_w, env_w, env_w_size))) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		goto error_exit;
	}
	free(name_w);

	if(!(env = p_utf16_to_alloc_utf8(env_w))) goto error_exit;
	free(env_w);

	return env;
error_exit:
	free(name_w);
	free(env_w);
	free(env);
	return NULL;
}

long OAL_get_user_data_dir(char *buffer, long size)
{
	char *LOCALAPPDATA_env = NULL;
	long return_val = -1;
	long min_buf_size;

	if(!(LOCALAPPDATA_env = get_alloc_env_str("LOCALAPPDATA"))) {
		goto error_exit;
	}

	min_buf_size = strlen(LOCALAPPDATA_env) + 2;
	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		return_val = min_buf_size;
		goto error_exit;
	}

	strcpy(buffer, LOCALAPPDATA_env);
	buffer[min_buf_size - 2] = OS_DIR_SEPARATOR;
	buffer[min_buf_size - 1] = '\0';
	return_val = 0;
error_exit:
	free(LOCALAPPDATA_env);
	return return_val;
}

static DWORD executable_path_wrapper(wchar_t *buf_w, DWORD size)
{
	return GetModuleFileNameW(NULL, buf_w, size);
}

static DWORD working_dir_wrapper(wchar_t *buf_w, DWORD size)
{
	return GetCurrentDirectoryW(size, buf_w);
}

/* Since WIN32 functions to query paths are quite similar, we can avoid any
 * code duplication by passing a wrapper as a function pointer for each path */
static long get_win32_api_path(char *buffer, long size, bool add_slash,
		DWORD (*win32_wrapper)(wchar_t *buffer, DWORD size))
{
	wchar_t *buf_w = NULL;
	char *tmp_buf = NULL;
	long max_fp_len, min_buf_size;
	long rtrn_val = -1;

	if((max_fp_len = OAL_get_max_filepath_len()) == -1) goto error_exit;
	else if(!(buf_w = malloc(max_fp_len * sizeof(wchar_t)))) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		goto error_exit;
	} else if(!win32_wrapper(buf_w, max_fp_len)) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		goto error_exit;
	}
	if(!(tmp_buf = p_utf16_to_alloc_utf8(buf_w))) goto error_exit;

	min_buf_size = strlen(tmp_buf) + 1;
	if(add_slash) ++min_buf_size;

	if(size < min_buf_size) {
		p_set_error(OAL_ERROR_BUFFER_SIZE);
		rtrn_val = min_buf_size;
		goto error_exit;
	}

	strcpy(buffer, tmp_buf);
	if(add_slash) {
		long buf_len = strlen(buffer);

		buffer[buf_len] = OS_DIR_SEPARATOR;
		buffer[buf_len + 1] = '\0';
	}
	rtrn_val = 0;
error_exit:
	free(buf_w);
	free(tmp_buf);
	return rtrn_val;
}

long OAL_get_executable_path(char *buffer, long size)
{
	return get_win32_api_path(buffer, size, false, executable_path_wrapper);
}

long OAL_get_working_dir(char *buffer, long size)
{
	return get_win32_api_path(buffer, size, true, working_dir_wrapper);
}

long OAL_get_max_filepath_len(void)
{
	/* Long file paths are not supported - not a big deal since they are not
	 * enabled by default. */
	return 260; 
}
#endif
