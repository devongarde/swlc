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

#include "attribute.h"
#include "directory.h"
#include "context.h"
#include "myhtml/api.h"

class element
{   myhtml_tree_node_t *node_;
public:
    element () : node_ (nullptr) { }
    element (myhtml_tree_node_t* n) : node_ (n) { }
    element child () const { return element (myhtml_node_child (node_)); }
    void next () { if (is_valid ()) node_ = myhtml_node_next (node_); }
    myhtml_tag_id_t tag () const { return myhtml_node_tag_id (node_); }
    attribute property () const { return attribute (myhtml_node_attribute_first (node_)); }
    void verify_children (const directory& d, context& c) const;
    void verify_self (const directory& d, context& c) const;
    bool is_valid () const { return node_ != nullptr; }
    bool has_url () const; };
