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

#ifndef PRIVATE_FUNCS_WIN_NT_H
#define PRIVATE_FUNCS_WIN_NT_H

#include <stddef.h>

/* Error codes are set if these functions fails. You do not need to set them
 * yourself. */
wchar_t *p_utf8_to_alloc_utf16(const char *src);
char *p_utf16_to_alloc_utf8(const wchar_t *src);

#endif
