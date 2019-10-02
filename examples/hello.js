#!/usr/bin/env gjs-console

// hello.js
// Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>

// This file is part of giqt

// giqt is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// giqt is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

const System = imports.system;

imports.gi.versions.Gtk = '3.0';
imports.gi.versions.Qt = '1.0';

const Gtk = imports.gi.Gtk;
const Qt = imports.gi.Qt;

Gtk.init(null);

let app = new Qt.Application();

app.connect('activate', () => {
    let win = new Qt.Widget();
    let label = new Qt.Label({label: "Hello GNU! from javascript"});
    let view = new Qt.WebView();
    view.load_uri('https://www.gnu.org');
    win.add(view);
    win.add(label);
    win.show_all();
});

app.run([System.programInvocationName].concat(ARGV));
