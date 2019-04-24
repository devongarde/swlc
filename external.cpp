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
#include "external.h"
#include "common.h"
#include <iostream>
#include <string>
#include <boost/process.hpp>
#include <boost/lexical_cast.hpp>
#include <windows.h>

using namespace boost::process;
using boost::lexical_cast;
using boost::bad_lexical_cast;

bool test_http (context& c, const ::std::string& url, bool is_http)
{   ipstream pipe_stream;
    int code = 0;
    ::std::string line, cmdline;
    if (is_http)
       cmdline = "curl -o NUL --silent --head --write-out %{http_code} ";
    else
       cmdline = "curl -o NUL --silent --head --ssl-norevoke -3 --write-out %{http_code} ";

    cmdline += url;
    if (c.verbose ()) ::std::cout << c.filename () << " : " << cmdline << "\n";
    try
    {   child baby (cmdline, std_out > pipe_stream);
        while (pipe_stream && ::std::getline (pipe_stream, line) && ! line.empty ())
            if (! code) code = lexical_cast <int> (line);
        baby.wait(); }
    catch (...)
    {   ::std::cerr << "Cannot check external links. Please check your installation of curl.\n";
        c.external (false);
        return true; }
    c.code (code);
    if (c.verbose ()) ::std::cout << "got " << code << ".\n"; }

bool test_connection (context& c, const ::std::string& url)
{   size_t colon = url.find (':');
    if (colon == ::std::string::npos) return false;
    if (colon < 2) return false;
    ::std::string protocol = url.substr (0, colon);
    if (compare_no_case (protocol, HTTP_PROTOCOL))
        return test_http (c, url, true);
    if (compare_no_case (protocol, HTTPS_PROTOCOL))
        return test_http (c, url, false);
    if (c.debug ()) ::std::cout << c.filename () << " unable to test " << url << ".\n";
    return true; }



bool external::verify (context& c, const ::std::string& url)
{   if (! url.empty ())
    {   auto e = url_.find (url);
        c.repeated (e != url_.end ());
        if (c.repeated ()) c.code (e -> second);
        else
        {   if (! test_connection (c, url)) c.code (400);
            url_.insert (value_t (url, c.code ())); }
    if (c.code () >= 400 && c.code () < 500) return false;
    return ((c.code () != 301) && (c.code () != 308)); };



c.code (400); return false; }