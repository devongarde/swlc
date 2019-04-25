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

#include "common.h"
#include "external.h"
#include "context.h"
#include <boost/filesystem.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

class directory
{   typedef ::std::shared_ptr <directory> self_ptr;
    typedef ::std::unordered_map < ::std::string, self_ptr > map_t;
    typedef map_t::value_type value_t;
    ::boost::filesystem::path path_;
    map_t content_;
    const directory* mummy_;
    static directory* root_;
    static external external_;
    bool add_to_content (::boost::filesystem::directory_entry& i);
    bool is_present (::boost::filesystem::path::iterator& i, const ::boost::filesystem::path::iterator& last) const;
    bool scan ();
public:
    explicit directory (const ::std::string& name, const directory* mummy = nullptr) : path_ (name), mummy_ (mummy)
    {   if (root_ == nullptr) root_ = this;
        if (is_valid ()) scan (); }
    static void set_root (directory* root) { root_ = root; }
    const ::std::string& name () const { return path_.filename ().string (); }
    bool is_valid () const;
    bool is_present (const ::boost::filesystem::path& link) const;
    bool add_virtual (const ::std::string& virt, const ::std::string& path);
    void verify (context& c) const;
    void verify_url (context& c, const ::std::string& url) const;
    void verify_external (context& c, const ::std::string& url) const;
    void report (const ::std::string& indent) const; };

bool add_virtual (directory& d, const ::std::string& assignment);
::std::string read_text_file (const ::std::string& name);
inline bool is_webpage (const ::std::string& name, const vstr_t& extensions);
