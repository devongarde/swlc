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

#include "context.h"
#include "element.h"
#include <string>
#include <iostream>

void element::verify_self (const directory& d, context& c) const
{   if (tag () == MyHTML_TAG_BASE)
    {    for (attribute a = property (); a.is_valid (); a.next ())
            if (a.is_href ())
            {   ::std::string href (a.value ());
                if (href.empty ())
                {   ::std::cerr << c.filename () << " has empty base element.\n"; }
                else if (href.find (':') != ::std::string::npos)
                {   if (c.verbose ()) ::std::cerr << c.filename ()  << " has offsite base " << a.value () << ", abandoning check.\n";
                    return; }
                if (href.at (0) == '#')
                {  if (c.verbose ()) ::std::cerr << c.filename ()  << " ignoring bizarre base " << a.value () << ".\n"; }
                c.base (href); } }
    else if (c.microdata () || has_url ())
    {   for (attribute a = property (); a.is_valid (); a.next ())
            if (a.url_expected (c)) d.verify_url (c, a.value ()); }
    verify_children (d, c); }

void element::verify_children (const directory& d, context& c) const
{   if (is_valid ())
        for (element e = child (); e.is_valid (); e.next ())
            e.verify_self (d, c); }

bool element::has_url () const
{   switch (tag ())
    {   case MyHTML_TAG_A :
		case MyHTML_TAG_APPLET :
        case MyHTML_TAG_AREA :
		case MyHTML_TAG_ARTICLE :
        case MyHTML_TAG_AUDIO :
        case MyHTML_TAG_BLOCKQUOTE :
        case MyHTML_TAG_DEL :
        case MyHTML_TAG_EMBED :
        case MyHTML_TAG_FORM :
        case MyHTML_TAG_FRAME :
        case MyHTML_TAG_HEAD :
        case MyHTML_TAG_IFRAME :
        case MyHTML_TAG_IMG :
        case MyHTML_TAG_INPUT :
        case MyHTML_TAG_INS :
		case MyHTML_TAG_LINK :
        case MyHTML_TAG_OBJECT :
        case MyHTML_TAG_Q :
        case MyHTML_TAG_SCRIPT :
        case MyHTML_TAG_SECTION :
        case MyHTML_TAG_SOURCE :
        case MyHTML_TAG_TRACK :
        case MyHTML_TAG_VIDEO :
            return true; }
    return false; }
