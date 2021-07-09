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

#include <stdlib.h>

#include "OAL_error.h"
#include "private_funcs.h"

/* The order of the array MUST match the order of the enum values. This ensures
 * a O(1) access time. */
const char *error_strs[] = {
	"No error happened", /* OAL_ERROR_NO_ERROR */
	"Allocation failed", /* OAL_ERROR_ALLOC_FAILED */
	"File does not exists", /* OAL_ERROR_FILE_NOT_EXISTS */
	"Invalid filesystem permissions", /* OAL_ERROR_FILE_PERMS */
	"File is not a directory", /* OAL_ERROR_NOT_A_DIR */
	"Missing environment variable", /* OAL_ERROR_MISSING_ENV */
	"Buffer size too small", /* OAL_ERROR_BUFFER_SIZE */
	"File is not a regular file", /* OAL_ERROR_NOT_A_REGULAR_FILE */
	"Unimplemented error code", /* OAL_ERROR_UNKNOWN_ERROR */
	"Error code does not exists", /* OAL_ERROR_NO_MATCH_ERROR */
	"Invalid fopen mode" /* OAL_ERROR_INVALID_MODE */
};

OAL_error OAL_get_last_error(void)
{
	return p_get_current_error();
}

const char *OAL_get_error_str(OAL_error error)
{
	if(error >= OAL_ERROR_ENUM_END || error < 0) {
		p_set_error(OAL_ERROR_NO_MATCH_ERROR);
		return NULL;
	} else return error_strs[error];
}
