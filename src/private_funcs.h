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

#ifndef PRIVATE_FUNCS_H
#define PRIVATE_FUNCS_H

#include "private_consts.h"
#include "OAL_error.h"

bool OAL_is_dir_separator(char ch);

void p_set_error(OAL_error error);
OAL_error p_get_current_error(void);
#endif
