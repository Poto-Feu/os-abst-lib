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
#include <string.h>
#include <unistd.h>

#include "OsAbstLib.h"
#include "private_consts.h"

#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
#include "win_nt/private_funcs_win_nt.h"
#endif

/* Code style rules are greatly relaxed for writing tests */

static void test_errors(void)
{
	char *exec_dir;
	OAL_error error_code = OAL_get_last_error();
	long max_filepath_len;
	long wrong_dir_len;

	assert(error_code == OAL_ERROR_NO_ERROR);
	assert((max_filepath_len = OAL_get_max_filepath_len()) != -1);
	assert((exec_dir = calloc(max_filepath_len, sizeof(char))));

	for(wrong_dir_len = 0; wrong_dir_len < 3; ++wrong_dir_len) {
		assert(OAL_get_executable_dir(exec_dir, wrong_dir_len) != 0);
		assert(OAL_get_working_dir(exec_dir, wrong_dir_len) != 0);
		assert(OAL_get_user_data_dir(exec_dir, wrong_dir_len) != 0);
	}
	free(exec_dir);
}

static void test_win_utf8(void)
{
#if OAL_TARGET_OS == OAL_OS_WINDOWS_NT
	const char *utf8_file = "test_utf8_file.txt";
	char *utf8_str;
	wchar_t *utf16_str;
	FILE *file_stream = OAL_open_file(utf8_file, "a+b");

	utf16_str = p_utf8_to_alloc_utf16("সﺽ");
	utf8_str = p_utf16_to_alloc_utf8(utf16_str);
	fputs(utf8_str, file_stream);
	fclose(file_stream);

	remove(utf8_file);
	free(utf8_str);
	free(utf16_str);
#endif
}

static void test_paths(void)
{
	char *working_dir, *user_data_dir, *exec_dir;
	long exec_dir_len = OAL_get_executable_dir_len();
	long working_dir_len = OAL_get_working_dir_len();
	long user_data_dir_len = OAL_get_user_data_dir_len();
	long max_filepath_len = OAL_get_max_filepath_len();

	assert(exec_dir_len != -1);
	assert(working_dir_len != -1);
	assert(user_data_dir_len != -1);

	working_dir = calloc(working_dir_len, sizeof(char));
	user_data_dir = calloc(user_data_dir_len, sizeof(char));
	assert((exec_dir = calloc(max_filepath_len, sizeof(char))));

	assert(OAL_get_executable_dir(exec_dir, exec_dir_len) == 0);
	assert(OAL_get_working_dir(working_dir, working_dir_len) == 0);
	assert(OAL_get_user_data_dir(user_data_dir, user_data_dir_len) == 0);

	printf("executable directory: %s\n", exec_dir);
	printf("working directory: %s\n", working_dir);
	printf("user data path: %s\n", user_data_dir);

	assert(exec_dir_len == (long)strlen(exec_dir) + 1);
	assert(working_dir_len == (long)strlen(working_dir) + 1);
	assert(user_data_dir_len == (long)strlen(user_data_dir) + 1);

	free(exec_dir);
	free(working_dir);
	free(user_data_dir);
}

static bool create_empty_text_file(const char *path)
{
	FILE *text_file;

	if(!(text_file = OAL_open_file(path, "a+b"))) return false;
	else {
		fclose(text_file);
		return true;
	}
}

static void test_text_files(void)
{
	const char *text_file_strs[] = {
		"test_dir/text.txt",
		"test_dir/text-2.txt",
		/* An U+056D unicode character is used to test internal UTF-8
		 * conversions. */
		"test_dir/text-3խ.txt",
	};
	size_t i;

	for(i = 0; i < sizeof(text_file_strs) / sizeof(text_file_strs[0]);
			++i) {
		assert(create_empty_text_file(text_file_strs[i]));
		assert(OAL_is_file_regular(text_file_strs[i]) == 0);
	}
	assert(OAL_remove_file(text_file_strs[2]) == 0);
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

static void test_dirs(void)
{
	const char *dir_strs[] = {
		"test_dir/test_dir_sub/",
		"test_dir2/test_dir_sub",
		"test_dir3/test_dir_sub"
	};
	const char *fake_dir_str = "test_dir58/test_dir_sub/";
	const char *rendundant_dir_str = "test_dir2/test_dir_sub/";
	size_t i;

	for(i = 0; i < sizeof(dir_strs) / sizeof(dir_strs[0]); ++i) {
		assert(OAL_create_dir(dir_strs[i]) == 0);
	}
	assert(OAL_is_file_regular(dir_strs[0]) != 0);
	assert(OAL_file_exists(fake_dir_str) != 0);
	assert(OAL_file_exists(rendundant_dir_str) == 0);

	test_text_files();

	for(i = 0; i < sizeof(dir_strs) / sizeof(dir_strs[0]); ++i) {
		char *str_dup = OAL_strdup(dir_strs[i]);
		char *slash_ptr = strchr(str_dup, '/');

		*slash_ptr = '\0';
		rmdir_recurs_relative(str_dup);
		free(str_dup);
	}
}

static void test_string(void)
{
	char *test_strdup_str;

	assert((test_strdup_str = OAL_strdup("test string strdup")));
	free(test_strdup_str);
}

int main(void)
{
	test_errors();
	test_win_utf8();
	test_string();
	test_paths();
	test_dirs();

	return EXIT_SUCCESS;
}
