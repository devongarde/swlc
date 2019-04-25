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

#include "common.h"
#include "context.h"
#include <boost/program_options.hpp>

class options
{   bool valid_;
	::boost::program_options::variables_map var_;
    void help (const ::boost::program_options::options_description& aid) const;
public:
	options () : valid_ (false) { }
 	bool is_valid () const { return valid_; }
	bool process (int argc, char** argv);
    void contextualise (context& c);
    void report () const; };
