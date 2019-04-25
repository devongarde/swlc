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

#include "common.h"
#include "directory.h"
#include "attribute.h"
#include "element.h"
#include "page.h"
#include "context.h"
#include <iostream>

int main (int argc, char** argv)
{   attribute::init ();
    context c (argc, argv);
    if (! c.is_valid ()) return 3;
    if (c.verbose ()) ::std::cout << "Collecting information...\n";
    directory d (c.root ());
    vstr_t virt (c.virtuals ());
    for (::std::string v : virt)
        add_virtual (d, v);
    if (c.debug ()) d.report ("");
    if (c.verbose ()) ::std::cout << "Checking links...\n";
    d.verify (c); }
