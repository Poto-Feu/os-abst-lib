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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "OsAbstLib.h"

/* Code style rules are greatly relaxed for writing tests */
int main(void)
{
	size_t max_filepath_len = OAL_get_max_filepath_len();
	size_t exec_dir_len = OAL_get_executable_dir_len();
	size_t work_dir_len = OAL_get_working_dir_len();
	size_t user_data_dir_len = OAL_get_user_data_dir_len();
	char *exec_dir = calloc(max_filepath_len, sizeof(char));
	char *working_dir = calloc(work_dir_len, sizeof(char));
	char *user_data_dir = calloc(user_data_dir_len, sizeof(char));
	char *test_strdup_str = OAL_strdup("test string strdup");

	assert(max_filepath_len != 0);
	assert(exec_dir_len != 0);
	assert(work_dir_len != 0);
	assert(user_data_dir_len != 0);
	assert(test_strdup_str);

	free(test_strdup_str);
	printf("exec_dir_length: %zu\n", exec_dir_len);
	printf("work_dir_length: %zu\n", work_dir_len);
	printf("user_data_dir_length: %zu\n", user_data_dir_len);

	assert(OAL_create_dir("test_dir/test_dir_sub/") == 0);
	assert(OAL_create_dir("test_dir2/test_dir_sub") == 0);
	assert(OAL_create_dir("test_dir3/test_dir_sub") == 0);
	assert(OAL_file_exists("test_dir58/test_dir_sub/") != 0);
	assert(OAL_file_exists("test_dir2/test_dir_sub/") == 0);

	assert(OAL_get_executable_dir(exec_dir, exec_dir_len) == 0);
	assert(OAL_get_working_dir(working_dir, work_dir_len) == 0);
	assert(OAL_get_user_data_dir(user_data_dir, user_data_dir_len) == 0);

	for(unsigned int wrong_dir_len = 0; wrong_dir_len < 3; ++wrong_dir_len) {
		assert(OAL_get_executable_dir(exec_dir, wrong_dir_len) != 0);
		assert(OAL_get_working_dir(working_dir, wrong_dir_len) != 0);
		assert(OAL_get_user_data_dir(user_data_dir, wrong_dir_len) != 0);
	}

	printf("executable directory: %s\n", exec_dir);
	printf("working directory: %s\n", working_dir);
	printf("user data path: %s\n", user_data_dir);
	free(exec_dir);
	free(working_dir);
	free(user_data_dir);

	return EXIT_SUCCESS;
}
