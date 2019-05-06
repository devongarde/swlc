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
#include "myhtml/api.h"
#include <unordered_set>
#include <boost/algorithm/string.hpp>

class attribute
{  typedef ::std::unordered_set < ::std::string > symbol_t;
    myhtml_tree_attr_t *attribute_;
    static symbol_t symbol_;

public:
    attribute () : attribute_ (nullptr) { }
    explicit attribute (myhtml_tree_attr_t* a) : attribute_ (a) { }
    static void init ();
    void next () { if (is_valid ()) attribute_ = myhtml_attribute_next (attribute_); }
    const char* key () const { return myhtml_attribute_key (attribute_, NULL); }
    const char* value () const { return myhtml_attribute_value (attribute_, NULL); }
    bool is_valid () const { return attribute_ != nullptr; }
    bool is_interesting () const { return (value () != nullptr) && (key () != nullptr); }
    bool is_href () const { return ::boost::algorithm::to_lower_copy (::std::string (key ())) == "href"; }
    bool url_expected (context& c) const; };
