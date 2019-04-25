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

#include "attribute.h"

#define ACTION      "action"
#define CITE        "cite"
#define CLASSID     "classid"
#define CODEBASE    "codebase"
#define DATA        "data"
#define HREF        "href"
#define ITEMTYPE    "itemtype"
#define PROFILE     "profile"
#define SRC         "src"
#define USEMAP      "usemap"

attribute::symbol_t attribute::symbol_;

void attribute::init ()
{   const char* const symbol_table [] =
    {  ACTION, CITE, CLASSID, CODEBASE, DATA, HREF, ITEMTYPE, PROFILE, SRC, USEMAP };

    for (int i = 0; i < sizeof (symbol_table) / sizeof (char *); ++i)
        symbol_.insert (symbol_table [i]); }

bool attribute::url_expected (context& c) const
{   if (is_boring ()) return false;
    symbol_t::const_iterator i = symbol_.find (::boost::algorithm::to_lower_copy (::std::string (key ())));
    if (i == symbol_.cend ()) return false;
    if (c.microdata ()) return true;
    return (i -> at (0) != 'i'); }
