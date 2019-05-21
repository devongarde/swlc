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

#include "context.h"
#include <unordered_map>
#include <string>

#define HTTP_PROTOCOL       "http"
#define HTTPS_PROTOCOL      "https"

class external
{   typedef ::std::unordered_map < ::std::string, int > map_t;
    typedef map_t::value_type value_t;
    map_t url_;
public:
    bool verify (context& c, const ::std::string& url); };
