/*
swlc (static website link checker)
Copyright (C) 2019 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public
License along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include <string>
#include <vector>

typedef ::std::vector < ::std::string > vstr_t;

inline bool cnc_test (unsigned char a, unsigned char b)
{ return ::std::tolower (a) == ::std::tolower (b); }

inline bool compare_no_case (const std::string& a, const std::string& b)
{   if (a.length () != b.length ()) return false;
    return ::std::equal (b.begin (), b.end (), a.begin (), cnc_test); }

inline bool is_one_of (const ::std::string& s, const vstr_t& v)
{   for (::std::string i : v)
        if (compare_no_case (s, i)) return true;
    return false; }
