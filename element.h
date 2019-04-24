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
    void verify (const directory& d, context& c) const;
    bool is_valid () const { return node_ != nullptr; } };

inline bool is_base (element& e) { return (e.tag () == MyHTML_TAG_BASE); }
inline bool is_form (element& e) { return (e.tag () == MyHTML_TAG_FORM); }
inline bool is_head (element& e) { return (e.tag () == MyHTML_TAG_HEAD); }
inline bool is_object (element& e) { return (e.tag () == MyHTML_TAG_OBJECT); }

inline bool has_cite (element& e)
{   switch (e.tag ())
    {   case MyHTML_TAG_ARTICLE :
        case MyHTML_TAG_BLOCKQUOTE :
        case MyHTML_TAG_DEL :
        case MyHTML_TAG_INS :
        case MyHTML_TAG_Q :
        case MyHTML_TAG_SECTION :
            return true; }
    return false; }

inline bool has_codebase (element& e)
{   switch (e.tag ())
    {   case MyHTML_TAG_APPLET :
		case MyHTML_TAG_OBJECT :
            return true; }
    return false; }

inline bool has_href (element& e)
{   switch (e.tag ())
    {   case MyHTML_TAG_A :
        case MyHTML_TAG_AREA :
		case MyHTML_TAG_FRAME :
		case MyHTML_TAG_LINK :
            return true; }
    return false; }

inline bool has_src (element& e)
{   switch (e.tag ())
    {   case MyHTML_TAG_AUDIO :
        case MyHTML_TAG_EMBED :
        case MyHTML_TAG_IFRAME :
        case MyHTML_TAG_IMG :
        case MyHTML_TAG_INPUT :
        case MyHTML_TAG_SCRIPT :
        case MyHTML_TAG_SOURCE :
        case MyHTML_TAG_TRACK :
        case MyHTML_TAG_VIDEO :
            return true; }
    return false; }

inline bool has_usemap (element& e)
{   switch (e.tag ())
    {   case MyHTML_TAG_IMG :
        case MyHTML_TAG_INPUT :
		case MyHTML_TAG_OBJECT :
            return true; }
    return false; }
