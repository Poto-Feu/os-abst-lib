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

#ifndef OAL_ERROR_H
#define OAL_ERROR_H

/**
 * @file OAL_error.h
 *
 * @brief Error-related functions and variables.
 */

/**
 * @brief Error codes for OsAbstLibrary functions.
 */
typedef enum {
	/** No function failed (yet) */
	OAL_ERROR_NO_ERROR = 0,
	/** Allocation failed (malloc, realloc etc...) */
	OAL_ERROR_ALLOC_FAILED = 1,
	/** The specified path does not point to an existing file */
	OAL_ERROR_FILE_NOT_EXISTS = 2,
	/** The required filesystem permissions are not present */
	OAL_ERROR_FILE_PERMS = 3,
	/** The specified file path does not point to a directory */
	OAL_ERROR_NOT_A_DIR = 4,
	/** A required environment variable is not defined */
	OAL_ERROR_MISSING_ENV = 5,
	/** The specified buffer size is too small */
	OAL_ERROR_BUFFER_SIZE = 6,
	/** The specified file path does not point to a regular file */
	OAL_ERROR_FILE_NOT_REGULAR = 7,
	/** An error occured but no specific error code is implemented - this may be
	 * used for some edge cases. */
	OAL_ERROR_UNKNOWN_ERROR = 8,
	/** The specified error code does not exists */
	OAL_ERROR_NO_MATCH_ERROR = 9,
	/** The fopen mode is invalid */
	OAL_ERROR_INVALID_MODE = 10,
	/** Used internally by OsAbstLibrary - do not use it */
	OAL_ERROR_ENUM_END
} OAL_error;

/**
 * @brief Fetch the last set error code.
 *
 * The error value is updated if an OsAbstLibrary function failed. Ironically,
 * this function cannot fail.
 *
 * @return the last set error code.
 */
OAL_error OAL_get_last_error(void);

/**
 * @brief Fetch the string matching the specified error code.
 *
 * This function might fail but it will set a "correct" error code if so.
 *
 * @param error the error code
 * @return the matching error string if found,
 * else NULL
 */
const char *OAL_get_error_str(OAL_error error);
#endif
