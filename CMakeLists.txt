cmake_minimum_required(VERSION 3.12)

project(OsAbstLib VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "CMAKE_BUILD_TYPE not set - defaulting to Release")
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-Wall -Wextra -pedantic -Wstrict-prototypes -Wvla)
else()
	message(WARNING "compiler and linker flags are only set if Clang or GCC is used")
endif()

add_library(OsAbstLib SHARED
	src/unix/os_paths_unix.c
	src/win_nt/os_paths_win_nt.c
	src/os_dir.c
	src/os_file.c
	src/os_paths.c
	src/os_string.c
	src/os_type.c
	src/private_funcs.c)

if(ENABLE_TESTS)
	add_executable(OAL-tests
		src/tests.c)

	target_link_libraries(OAL-tests OsAbstLib)
	target_include_directories(OAL-tests PRIVATE include)
endif()

target_include_directories(OsAbstLib PRIVATE src)
target_include_directories(OsAbstLib PRIVATE include)

# This is necessary or Clang may complain about missing headers/libs
if(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
	include_directories(SYSTEM /usr/local/include)
	link_directories(/usr/local/lib)
endif()

set_target_properties(OsAbstLib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(OsAbstLib PROPERTIES SOVERSION 0.1)

set_target_properties(OsAbstLib PROPERTIES PUBLIC_HEADER "include/OsAbstLib.h;include/OAL_flags.h;\
include/os_dir.h;include/os_file.h;include/os_paths.h;include/os_string.h;include/os_type.h")

include(GNUInstallDirs)

install(TARGETS OsAbstLib
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OsAbstLib)

add_custom_target(
	copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_BINARY_DIR}/compile_commands.json
		${CMAKE_CURRENT_LIST_DIR})
