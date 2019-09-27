/*
 * qt-window.h
 * Copyright (C) 2017-2019 Michael Rosset <mike.rosset@gmail.com>
 *
 * This file is part of giqt
 *
 * giqt is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 * giqt is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _QT_WINDOW_H_
#define _QT_WINDOW_H_

#include "qt-application.h"
#include <gtk/gtk.h>
G_BEGIN_DECLS

/*
 * Type declaration.
 */

#define QT_TYPE_WINDOW qt_window_get_type ()
G_DECLARE_FINAL_TYPE (QtWindow, qt_window, QT, WINDOW, GtkWidget)

/*
 * Constructors
 */

QtWindow *qt_window_new ();

/*
 * Method definitions.
 */

void qt_window_show (GtkWidget *widget);

G_END_DECLS

#endif /* _QT_WINDOW_H_ */
