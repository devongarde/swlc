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
#include <iostream>

class context
{   bool debug_, external_, forwarded_, microdata_, once_, repeated_, revoke_, valid_, verbose_;
    int code_;
    ::std::string base_, filename_, index_, root_;
    vstr_t extensions_, site_, virtuals_;
public:
    context (int argc, char** argv);
    const ::std::string base () const { return base_; }
    bool debug () const { return debug_; }
    int code () const { return code_; }
    const vstr_t extensions () const { return extensions_; }
    bool external () const { return external_; }
    const ::std::string filename () const { return filename_; }
    bool forwarded () const { return forwarded_; }
    const ::std::string index () const { return index_; }
    bool microdata () const { return microdata_; }
    bool once () const { return once_; }
    bool repeated () const { return repeated_; }
    bool revoke () const { return revoke_; }
    const ::std::string root () const { return root_; }
    const vstr_t site () const { return site_; }
    bool verbose () const { return verbose_; }
    const vstr_t virtuals () const { return virtuals_; }
    bool is_valid () const { return valid_; }
    context& base (const ::std::string& s) { base_ = s; return *this; }
    context& code (const int i) { code_ = i; return *this; }
    context& debug (const bool b) { debug_ = b; return *this; }
    context& extensions (const vstr_t& s) { extensions_ = s; return *this; }
    context& external (const bool b) { external_ = b; return *this; }
    context& filename (const ::std::string& s) { filename_ = s; return *this; }
    context& forwarded (const bool b) { forwarded_ = b; return *this; }
    context& index (const ::std::string& s) { index_ = s; return *this; }
    context& microdata (const bool b) { microdata_ = b; return *this; }
    context& once (const bool b) { once_ = b; return *this; }
    context& repeated (const bool b) { repeated_ = b; return *this; }
    context& revoke (const bool b) { revoke_ = b; return *this; }
    context& root (const ::std::string& s) { root_ = s; return *this; }
    context& site (const vstr_t& s) { site_ = s; return *this; }
    context& verbose (const bool b) { verbose_ = b; return *this; }
    context& virtuals (const vstr_t& s) { virtuals_ = s; return *this; } };
