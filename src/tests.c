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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <OsAbstLib/OsAbstLib.h>

/* Code style rules are greatly relaxed for writing tests */
int main(void)
{
	size_t max_filepath_length = OAL_get_max_filepath_length();
	assert(max_filepath_length != 0);
	char *exec_dir = calloc(max_filepath_length, sizeof(char));
	char *working_dir = calloc(max_filepath_length, sizeof(char));

	assert(OAL_create_directory("test_dir/test_dir_sub/") == 0);
	assert(OAL_create_directory("test_dir2/test_dir_sub") == 0);
	assert(OAL_create_directory("test_dir3\\test_dir_sub") == 0);
	assert(OAL_create_directory("test_dir4\\test_dir_sub\\") == 0);
	assert(OAL_file_exists("test_dir58/test_dir_sub/") != 0);
	assert(OAL_file_exists("test_dir2\\test_dir_sub/") == 0);
	assert(OAL_get_executable_directory(exec_dir, max_filepath_length) == 0);
	assert(OAL_get_working_directory(working_dir, max_filepath_length) == 0);

	printf("executable directory: %s\n", exec_dir);
	printf("working directory: %s\n", working_dir);
	free(exec_dir);
	free(working_dir);

	return EXIT_SUCCESS;
}
