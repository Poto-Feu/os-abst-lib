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

#ifndef OAL_FLAGS_H
#define OAL_FLAGS_H

/**
 * @file OAL_flags.h
 *
 * DO NOT USE THIS HEADER! This file is not documented in Doxygen as it is meant for internal use
 * within the library only.
 */

#if defined(__GNUC__) || defined(__clang__)
#define OAL_FORCEINLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define OAL_FORCEINLINE __forceinline
#else
/* There is no standard way to force a function to be inline. However, this may acts as a hint for
 * some compilers and using the inline keyword presents no downside. */
#define OAL_FORCEINLINE inline
#endif

#endif
