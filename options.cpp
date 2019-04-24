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
#include "version.h"
#include "options.h"
#include <iostream>

#define DEBUG       "debug"
#define EXTENSION   "extension"
#define EXTERNAL    "external"
#define FILE        "file"
#define HELP        "help"
#define INDEX       "index"
#define MICRODATA   "microdata"
#define ONCE        "once"
#define ROOT        "root"
#define SITE        "site"
#define VERBOSE     "verbose"
#define VERSION     "version"
#define VIRTUAL     "virtual"

void options::help (const ::boost::program_options::options_description& aid) const
{   ::std::cout << PROG " [switch...] [file...]\n" << aid << "\n"; }

bool options::process (int argc, char** argv)
{   ::boost::program_options::options_description basic ("Console Options"), primary ("Standard Options"), hidden, cmd, config, aid;
	::boost::program_options::positional_options_description pos;
	pos.add (ROOT, 1);
	basic.add_options ()
        (HELP ",h", "output this information")
		(VERSION ",V", "display version and copyright info")
        ;
	hidden.add_options ()
        (ROOT, ::boost::program_options::value <::std::string> (), "website root directory, default current")
        ;
	primary.add_options ()
        (DEBUG ",d", "output debug information")
        (EXTENSION ",x", ::boost::program_options::value < vstr_t > (), "check files with this extension")
        (EXTERNAL ",e", "check external links (requires curl)")
        (INDEX ",i", ::boost::program_options::value <::std::string> (), "index file in directories (none if not defined).")
        (MICRODATA ",m", "check microdata itemtypes")
        (ONCE ",o", "report each broken external link once")
        (VERBOSE ",v", "output extra information")
        (SITE ",s", ::boost::program_options::value < vstr_t > (), "domain name for local site")
        (VIRTUAL ",l", ::boost::program_options::value < vstr_t > (), "define virtual directory, arg syntax directory=path")
		;
	cmd.add (basic).add (primary).add (hidden);
	config.add (primary).add (hidden);
	aid.add (basic).add (primary);
    try
    {   ::boost::program_options::store (::boost::program_options::command_line_parser (argc, argv).options (cmd).positional (pos).run (), var_); }
    catch (...)
    {   ::std::cout << "parameter error.\n";
        help (aid);
        return false; }
    ::boost::program_options::notify (var_);
	if (var_.count (VERSION)) ::std::cout << PROG " (" TITLE ") " VERSION_STRING "\n" COPYRIGHT "\n\n";
	if (argc < 2 || var_.count (HELP))
    {   help (aid);
		return false; }
    valid_ = argc > 1;
    return is_valid (); }

void options::contextualise (context& c)
{   c.debug (var_.count (DEBUG));
    if (var_.count (EXTENSION)) c.extensions ( var_ [EXTENSION].as < vstr_t > ());
    c.external (var_.count (EXTERNAL));
    if (var_.count (INDEX)) c.index (var_ [INDEX].as < ::std::string > ());
    c.once (var_.count (ONCE));
    c.microdata (var_.count (MICRODATA));
    if (var_.count (ROOT)) c.root (var_ [ROOT].as < ::std::string > ());
    if (var_.count (SITE)) c.site (var_ [SITE].as < vstr_t > ());
    c.verbose (var_.count (VERBOSE) || var_.count (DEBUG));
    if (var_.count (VIRTUAL)) c.virtuals (var_ [VIRTUAL].as < vstr_t > ()); };

void pvs (const vstr_t& data)
{   for (auto i : data)
        ::std::cout << i << " "; }

void options::report () const
{   if (var_.count (DEBUG)) ::std::cout << DEBUG "\n";
    if (var_.count (EXTENSION)) { ::std::cout << EXTENSION ": "; pvs (var_ [EXTENSION].as < vstr_t > ()); ::std::cout << "\n"; }
    if (var_.count (HELP)) ::std::cout << HELP "\n";
    if (var_.count (ROOT)) ::std::cout << ROOT ": " << var_ [ROOT].as< ::std::string > () << "\n";
    if (var_.count (INDEX)) ::std::cout << INDEX ": " << var_ [INDEX].as< ::std::string > () << "\n";
    if (var_.count (ONCE)) ::std::cout << ONCE "\n";
    if (var_.count (MICRODATA)) ::std::cout << MICRODATA "\n";
    if (var_.count (SITE)) { ::std::cout << SITE ": "; pvs (var_ [SITE].as < vstr_t > ()); ::std::cout << "\n"; }
    if (var_.count (VERSION)) ::std::cout << VERSION "\n";
    if (var_.count (VERBOSE)) ::std::cout << VERBOSE "\n";
    if (var_.count (VIRTUAL)) { ::std::cout << VIRTUAL ": "; pvs (var_ [VIRTUAL].as< vstr_t > ()); ::std::cout << "\n"; } }
