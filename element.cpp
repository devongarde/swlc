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

void element::verify (const directory& d, context& c) const
{   if (is_valid ())
        for (element e = child (); e.is_valid (); e.next ())
        {   if (is_base (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_href (a))
                    {   ::std::string href (a.value ());
                        if (href.empty ())
                        {   ::std::cerr << c.filename () << " has empty base element.\n"; }
                        else if (href.find (':') != ::std::string::npos)
                        {   if (c.verbose ()) ::std::cerr << c.filename ()  << " has offsite base " << a.value () << ", abandoning check.\n";
                            return; }
                        if (href.at (0) == '#')
                        {  if (c.verbose ()) ::std::cerr << c.filename ()  << " ignoring bizarre base " << a.value () << ".\n"; }
                        c.base (href); }
            if (is_object (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_classid (a) || is_data (a) || is_usemap (a) || is_name (a))
                        d.verify_url (c, a.value ());
            if (is_form (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_action (a)) d.verify_url (c, a.value ());
            if (is_head (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_profile (a)) d.verify_url (c, a.value ());
            if (has_cite (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_cite (a)) d.verify_url (c, a.value ());
            if (has_codebase (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_cite (a)) d.verify_url (c, a.value ());
            if (has_href (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_href (a)) d.verify_url (c, a.value ());
            if (has_src (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_src (a)) d.verify_url (c, a.value ());
            if (has_usemap (e))
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_usemap (a)) d.verify_url (c, a.value ());
            if (c.microdata ())
                for (attribute a = e.property (); a.is_valid (); a.next ())
                    if (is_itemtype (a)) d.verify_url (c, a.value ());
            e.verify (d, c); } }