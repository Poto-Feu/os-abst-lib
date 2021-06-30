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
#include "private_consts.h"

static bool create_empty_text_file(const char *path)
{
	FILE *text_file;

	if(!(text_file = fopen(path, "w"))) return false;
	else {
		fclose(text_file);
		return true;
	}
}

static void rmdir_recurs_relative(const char *dir)
{
	/* Ugly but it works and it's a test program so OK. */
#ifdef OAL_IS_POSIX
	const char *system_cmd = "rm -rf ";
#elif OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	const char *system_cmd = "rmdir /s /q ";
#endif
	char *full_system_cmd = malloc((strlen(system_cmd) + strlen(dir) + 1) *
			sizeof(char));

	strcpy(full_system_cmd, system_cmd);
	strcat(full_system_cmd, dir);
	/* "Y'know, don't say... swears" */
	system(full_system_cmd);
	free(full_system_cmd);
}

/* Code style rules are greatly relaxed for writing tests */
int main(void)
{
	const char *dir_strs[] = {
		"test_dir/test_dir_sub/",
		"test_dir2/test_dir_sub",
		"test_dir3/test_dir_sub"
	};
	const char *text_file_strs[] = {
		"test_dir/text.txt",
		"test_dir/text-2.txt",
		"test_dir/text-3.txt",
	};
	const char *fake_dir_str = "test_dir58/test_dir_sub/";
	const char *rendundant_dir_str = "test_dir2/test_dir_sub/";
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

	for(size_t i = 0; i < sizeof(dir_strs) / sizeof(dir_strs[0]); ++i) {
		assert(OAL_create_dir(dir_strs[i]) == 0);
	}
	assert(OAL_file_exists(fake_dir_str) != 0);
	assert(OAL_file_exists(rendundant_dir_str) == 0);

	for(size_t i = 0; i < sizeof(text_file_strs) / sizeof(text_file_strs[0]);
			++i) {
		assert(create_empty_text_file(text_file_strs[i]));
	}

	assert(OAL_get_dir_file_count("test_dir")
			== sizeof(text_file_strs) / sizeof(text_file_strs[0]));

	assert(OAL_get_executable_dir(exec_dir, exec_dir_len) == 0);
	assert(OAL_get_working_dir(working_dir, work_dir_len) == 0);
	assert(OAL_get_user_data_dir(user_data_dir, user_data_dir_len) == 0);

	for(unsigned int wrong_dir_len = 0; wrong_dir_len < 3; ++wrong_dir_len) {
		assert(OAL_get_executable_dir(exec_dir, wrong_dir_len) != 0);
		assert(OAL_get_working_dir(working_dir, wrong_dir_len) != 0);
		assert(OAL_get_user_data_dir(user_data_dir, wrong_dir_len) != 0);
	}
	for(size_t i = 0; i < sizeof(dir_strs) / sizeof(dir_strs[0]); ++i) {
		char *str_dup = OAL_strdup(dir_strs[i]);
		char *slash_ptr = strchr(str_dup, '/');

		*slash_ptr = '\0';
		rmdir_recurs_relative(str_dup);
		free(str_dup);
	}

	printf("executable directory: %s\n", exec_dir);
	printf("working directory: %s\n", working_dir);
	printf("user data path: %s\n", user_data_dir);
	free(exec_dir);
	free(working_dir);
	free(user_data_dir);

	return EXIT_SUCCESS;
}
