#!/usr/bin/env python

# example.py
# Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>

# This file is part of giqt

# giqt is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

# giqt is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

import gi
gi.require_version("Gtk", "3.0")
gi.require_version("Qt", "1.0")

from gi.repository import Gtk
from gi.repository import Qt

app = Qt.Application()
window = Qt.Widget()
view = Qt.WebView()
label = Qt.Label(label="Hello GNU! from python")
view.load_uri("http://www.gnu.org")
window.add(label);
window.add(view);
window.show()
app.run()
