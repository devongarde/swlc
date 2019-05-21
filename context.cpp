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
#include "options.h"

context::context (int argc, char** argv)
    : code_ (0), debug_ (false), external_ (false), forwarded_ (false), microdata_ (false), once_ (false),
      repeated_ (false), revoke_ (false), valid_ (false), verbose_ (false)
{   options o (argc, argv);
    if (o.is_valid ())
    {   o.contextualise (*this);
        if (verbose ()) o.report ();
        valid_ = ! root ().empty (); } }
