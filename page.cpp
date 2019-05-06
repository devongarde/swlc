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

#include "directory.h"
#include "common.h"
#include "page.h"
#include <iostream>
#include <string>

void page::init ()
{   html_ = myhtml_create ();
    if (html_ == nullptr) return;
    if (MyHTML_STATUS_OK != myhtml_init (html_, MyHTML_OPTIONS_DEFAULT, 1, 4096)) return;
    tree_ = myhtml_tree_create ();
    if (tree_ == nullptr) return;
    if (MyHTML_STATUS_OK != myhtml_tree_init (tree_, html_))
    {   myhtml_tree_destroy (tree_);
        tree_ = nullptr; } }

page::page (const ::std::string& content) : tree_ (nullptr), html_ (nullptr)
{   init ();
    if (! parse (content)) zap (); }

void page::zap ()
{   if (tree_ != nullptr)
    {   myhtml_tree_clean (tree_);
        myhtml_tree_destroy (tree_);
        tree_ = nullptr; }
    if (html_ != nullptr)
    {   myhtml_clean (html_);
        myhtml_destroy (html_);
        html_ = nullptr; } }

bool page::parse (const ::std::string& content)
{   if (! is_valid ()) return false;
    return (MyHTML_STATUS_OK == myhtml_parse (tree_, MyENCODING_DEFAULT, content.c_str (), content.length ())); }

void page::verify (const directory& d, context& c) const
{   element e (document ());
    ::std::string base;
    e.verify_children (d, c); }

void page::report () const
{   ::std::cout << "html_ ";
    if (html_ == nullptr) ::std::cout << "null";
    else ::std::cout << html_;
    ::std::cout << "\ntree_ ";
    if (html_ == nullptr) ::std::cout << "null";
    else ::std::cout << tree_;
    ::std::cout << "\n"; }

::std::string unescape (size_t pc, const ::std::string& url)
{   struct escape_t
    {   char encoding [4];
        char ch; }
    encoded [] =
    {   { "%20", ' ' },
        { "%23", '#' },
        { "%24", '$' },
        { "%25", '%' },
        { "%26", '&' },
        { "%2F", '/' },
        { "%3A", ':' },
        { "%3B", ';' },
        { "%3C", '<' },
        { "%3D", '=' },
        { "%3E", '>' },
        { "%3F", '?' },
        { "%40", '@' },
        { "%5B", '[' },
        { "%5C", '\\'},
        { "%5D", ']' },
        { "%5E", '^' },
        { "%60", '\''},
        { "%7B", '{' },
        { "%7C", '|' },
        { "%7D", '}' },
        { "%7E", '~' } };
    constexpr size_t max = sizeof (encoded) / sizeof (escape_t);
    ::std::string res (url);
    while (pc != ::std::string::npos)
    {   for (int i = 0; i < max; ++i)
            if (compare_no_case (res.substr (pc, 3), encoded [i].encoding))
            {   res.replace (pc, 3, ::std::string (1, encoded [i].ch));
                break; }
        pc = res.find ('%', pc + 1); }
    return res; }

::std::string sanitise (const ::std::string& url)
{   ::std::string res (url);
    size_t post = res.find ("://");
    if (post == ::std::string::npos) post = 0;
    else post += 2;
    while (true)
    {   size_t ds = res.find ("//", post);
        if (ds == ::std::string::npos) break;
        res.replace (ds, 2, "/"); }
    size_t pc = res.find ('%');
    if (pc != ::std::string::npos)
        res = unescape (pc, res);
    pc = res.find_first_of ("?#");
    if (pc != ::std::string::npos)
        res = res.substr (0, pc);
    return res; }
