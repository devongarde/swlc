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
#include "page.h"
#include "directory.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

using namespace boost::filesystem;

directory* directory::root_ = nullptr;
external directory::external_;


bool directory::is_present (::boost::filesystem::path::iterator& i, const ::boost::filesystem::path::iterator& last) const
{   if (i == last) return false;
    if (i -> empty ()) return false;
    if (i -> string () == ".") return is_present (++i, last);
    if (i -> string () == "..")
    {   if (mummy_ == nullptr) return false;
        return mummy_ -> is_present (++i, last); }
    auto e = content_.find (i -> string ());
    if (e == content_.end ()) return false;
    if (e -> second == nullptr) return true;
    return e -> second -> is_present (++i, last); }

bool directory::is_present (const ::boost::filesystem::path& link) const
{   if (link.empty ()) return false;
    auto i = link.begin ();
    if (i == link.end ()) return false;
    if (i -> string () == "/") return root_ -> is_present (++i, link.end ());
    return is_present (i, link.end ()); }

bool directory::scan ()
{   for (directory_entry& x : directory_iterator (path_))
        if (! add_to_content (x)) return false;
    return true; }

bool directory::add_to_content (::boost::filesystem::directory_entry& i)
{   if (is_regular_file (i.path ()))
        return content_.insert (value_t (i.path ().filename ().string (), nullptr)).second;
    if (is_directory (i.path ()))
        return content_.insert (value_t (i.path ().filename ().string (), new directory (i.path ().string (), this))).second;
    return false; }

bool directory::is_valid () const
{   return exists (path_) && is_directory (path_); }

bool directory::add_virtual (const ::std::string& virt, const ::std::string& path)
{   if (is_present (virt)) return false;
    return content_.insert (value_t (virt, new directory (path, this))).second; }

void directory::report (const ::std::string& indent) const
{   for (auto i : content_)
    {   ::std::cout << indent << i.first << "\n";
        if (i.second != nullptr)
            i.second->report (indent + " "); } }

void directory::verify (context& c) const
{   for (auto i : content_)
        if (i.second != nullptr)
            i.second -> verify (c);
        else if (is_webpage (i.first, c.extensions ()))
        {   path name (path_);
            name /= i.first;
            c.filename (name.string ());
            if (c.verbose ()) ::std::cout << "checking " << c.filename () << "\n";
            try
            {   ::std::string content (read_text_file (c.filename ()));
                if (! content.empty ())
                {   page web (content);
                    if (web.is_valid ())
                    {   web.verify (*this, c);
                        continue; } } }
            catch (...)
            {  }
            ::std::cerr << "Cannot parse " << c.filename () << "\n"; } }

void directory::verify_url (context& c, const ::std::string& url) const
{   if (url.empty ())
    {  ::std::cerr << c.filename () << " has an empty URL.\n";
        return; }
    if (url.at (0) == '#') return;
    ::std::string u (sanitise (url));
    if (u.empty ())
    {   ::std::cerr << c.filename () << " has duff URL " << url << ".\n";
        return; }
    size_t colon = u.find (':');
    if (colon != ::std::string::npos)
    {   if (u.length () < colon + 3)
        {   if (c.external ()) verify_external (c, url);
            return; }
        ::std::string lhs = u.substr (0, colon);
        if (! compare_no_case (lhs, HTTP_PROTOCOL) && ! compare_no_case (lhs, HTTPS_PROTOCOL))
        {   if (c.external ()) verify_external (c, url);
            return; }
        if (u.substr (colon + 1, 2) != "//")
        {   ::std::cerr << c.filename () << " has malformed URL " << url << "\n";
            return; }
        size_t eop = u.find ('/', colon + 3);
        if (eop == ::std::string::npos) eop = u.length ();
        if (! is_one_of (u.substr (colon + 3, eop - colon - 3), c.site ()))
        {   if (c.external ()) verify_external (c, url);
            return; }
        if (eop == u.length ()) u = "/";
        else u = u.substr (eop); }
    if (u.at (u.length () - 1) == '/')
        u += c.index ();
    path p (c.base ());
    p /= u;
    if (! is_present (p))
        ::std::cerr << c.filename () << " " << url << " is missing.\n"; }

void directory::verify_external (context& c, const ::std::string& url) const
{   if (external_.verify (c, url) || (c.repeated () && c.once ())) return;
    ::std::cerr << c.filename () << " " << url;
    switch (c.code ())
    {   case 301 :
        case 308 :
            ::std::cerr << " has moved";
            break;
        case 400 :
            ::std::cerr << " is malformed or bad";
            break;
        case 401 :
            ::std::cerr << " is unauthorised";
            break;
        case 403 :
            ::std::cerr << " is forbidden";
            break;
        case 404 :
        case 410 :
            ::std::cerr << " is broken";
            break;
        case 407 :
            ::std::cerr << " is blocked by a proxy";
            break;
        case 408 :
            ::std::cerr << " has timed out";
            break;
        case 451 :
            ::std::cerr << " is censored";
            break;
        default :
            ::std::cerr << " is unavailable";
            break; }
    ::std::cerr << " (" << c.code () << ").\n"; }


bool add_virtual (directory& d, const ::std::string& assignment)
{   size_t len = assignment.length ();
    size_t sz = assignment.find ('=');
    if (sz == ::std::string::npos || sz < 1 || sz >= len - 1) return false;
    return d.add_virtual (assignment.substr (0, sz), assignment.substr (sz + 1)); }

::std::string read_text_file (const::std::string& name)
{   path p (name);
    if (exists (p) && is_regular_file (p))
    {  ifstream f (name);
        if (! f.bad ())
        {   ::std::stringstream res;
            res << f.rdbuf ();
            f.close ();
            return res.str (); } }
    return ::std::string (); }

