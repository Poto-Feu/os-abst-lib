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
#include <assert.h>
#include <stdlib.h>

#include <errhandlingapi.h>
#include <stringapiset.h>
#include <winerror.h>

#include "win_nt/private_funcs_win_nt.h"
#include "OAL_string.h"
#include "private_funcs.h"

wchar_t *p_utf8_to_alloc_utf16(const char *src)
{
	wchar_t *utf16_str;
	int utf16_n_chars;

	if(!src) {
		p_set_error(OAL_ERROR_NULL_PTR);
		return NULL;
	}

	/* First, we need to get the required size of the buffer. */
	utf16_n_chars = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	if(!utf16_n_chars) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		return NULL;
	}

	utf16_str = malloc(utf16_n_chars * sizeof(wchar_t));
	if(!utf16_str) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		return NULL;
	} else if(!MultiByteToWideChar(CP_UTF8, 0,
				src, -1,
				utf16_str, utf16_n_chars)) {
#ifndef NDEBUG
		DWORD err = GetLastError();

		assert(err == ERROR_INSUFFICIENT_BUFFER);
#endif
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		free(utf16_str);
		return NULL;
	} else return utf16_str;
}

char *p_utf16_to_alloc_utf8(const wchar_t *src)
{
	char *utf8_str = NULL;
	int utf8_n_chars;

	if(!src) {
		p_set_error(OAL_ERROR_NULL_PTR);
		goto error_exit;
	}

	if(!(utf8_n_chars = WideCharToMultiByte(CP_UTF8, 0,
					src, -1,
					NULL, 0,
					NULL, NULL))) {
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		goto error_exit;
	}

	utf8_str = malloc(utf8_n_chars * sizeof(char));
	if(!utf8_str) {
		p_set_error(OAL_ERROR_ALLOC_FAILED);
		goto error_exit;
	} else if(!(WideCharToMultiByte(CP_UTF8, 0,
					src, -1,
					utf8_str, utf8_n_chars,
					NULL, NULL))) {
#ifndef NDEBUG
		DWORD err = GetLastError();

		assert(err == ERROR_INSUFFICIENT_BUFFER);
#endif
		p_set_error(OAL_ERROR_UNKNOWN_ERROR);
		goto error_exit;
	} else return utf8_str;

error_exit:
	free(utf8_str);
	return NULL;
}
#endif
