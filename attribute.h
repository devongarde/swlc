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
#include "myhtml/api.h"


class attribute
{   myhtml_tree_attr_t *attribute_;
public:
    attribute () : attribute_ (nullptr) { }
    attribute (myhtml_tree_attr_t* a) : attribute_ (a) { }
    void next () { if (is_valid ()) attribute_ = myhtml_attribute_next (attribute_); }
    const char* key () const { return myhtml_attribute_key (attribute_, NULL); }
    const char* value () const { return myhtml_attribute_value (attribute_, NULL); }
    bool is_valid () const { return attribute_ != nullptr; } };

inline bool is_action (const attribute& a) { return compare_no_case (a.key (), "action"); }
inline bool is_cite (const attribute& a) { return compare_no_case (a.key (), "cite"); }
inline bool is_classid (const attribute& a) { return compare_no_case (a.key (), "classid"); }
inline bool is_codebase (const attribute& a) { return compare_no_case (a.key (), "codebase"); }
inline bool is_data (const attribute& a) { return compare_no_case (a.key (), "data"); }
inline bool is_href (const attribute& a) { return compare_no_case (a.key (), "href"); }
inline bool is_itemtype (const attribute& a) { return compare_no_case (a.key (), "itemtype"); }
inline bool is_name (const attribute& a) { return compare_no_case (a.key (), "name"); }
inline bool is_profile (const attribute& a) { return compare_no_case (a.key (), "profile"); }
inline bool is_src (const attribute& a) { return compare_no_case (a.key (), "src"); }
inline bool is_usemap (const attribute& a) { return compare_no_case (a.key (), "usemap"); }
