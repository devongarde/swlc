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
#include <boost/process.hpp>

int main (int argc, char** argv)
{   attribute::init ();
    context c (argc, argv);
    if (! c.is_valid ()) return 3;
    if (c.verbose ()) ::std::cout << "Collecting information...\n";
    directory d (c.root ());
    vstr_t virt (c.virtuals ());
    try
    {   if (! d.scan ())
        {   ::std::cerr << "scan of " << c.root () << " failed.\n";
            return 3; }
        for (::std::string v : virt)
            if (! add_virtual (d, v))
            {   ::std::cerr << "scan of " << v << " failed.\n";
                return 3; } }
    catch (const ::boost::process::process_error& e)
    { ::std::cerr << "scan, process error " << e.code () << ": " << e.what () << "\n"; return 3; }
    catch (const ::std::system_error& e)
    { ::std::cerr << "scan, system error " << e.code () << ": " << e.what () << "\n"; return 3; }
    catch (...)
    { ::std::cerr << "scan, unknown exception\n"; return 3; }
    if (c.debug ()) d.report ("");
    if (d.empty ()) { ::std::cerr << "no content.\n"; return 2; }
    if (c.verbose ()) ::std::cout << "Checking links...\n";
    try
    { d.verify (c); }
    catch (const ::boost::process::process_error& e)
    { ::std::cerr << "verify process error " << e.code () << ": " << e.what () << "\n"; return 3; }
    catch (const ::std::system_error& e)
    { ::std::cerr << "verify, system error " << e.code () << ": " << e.what () << "\n"; return 3; }
    catch (...)
    { ::std::cerr << "verify, unknown exception\n"; return 3; }
    return 0; };
