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
#include <limits.h>
#include <string.h>

#include <errhandlingapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <minwinbase.h>
#include <winerror.h>

#include "OAL_dir.h"
#include "OAL_file.h"
#include "private_funcs.h"
#include "win_nt/private_funcs_win_nt.h"

int p_create_non_recursive_dir(const char *path)
{
	wchar_t *path_w;

	if(!(path_w = p_utf8_to_alloc_utf16(path))) return -1;
	else if(!CreateDirectoryW(path_w, NULL)) {
		DWORD err = GetLastError();

		free(path_w);
		if(err == ERROR_ALREADY_EXISTS) return 0;
		else return -1;
	} else {
		free(path_w);
		return 0;
	}
}
#endif
