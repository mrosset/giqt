/*
 * qt-widget.h
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

#ifndef _QT_PLUG_H_
#define _QT_PLUG_H_

#include <gtk/gtk.h>
#include <qt-application.h>

G_BEGIN_DECLS

#define QT_TYPE_WIDGET qt_plug_get_type ()
G_DECLARE_FINAL_TYPE (QtPlug, qt_plug, QT, PLUG, GtkBin);

typedef struct _QtPlug QtPlug;
typedef struct _QtPlugPrivate QtPlugPrivate;

struct _QtPlugClass
{
  GtkContainerClass parent_class;
};

struct _QtPlug
{
  GtkContainer parent_instance;

  QtPlugPrivate *priv;
};

QtPlug *qt_plug_new (void);

void qt_plug_fill_parent (GtkContainer *container, GtkWidget *widget);

void qt_plug_set_parent (QtPlug *widget, QtPlug *parent);

void qt_plug_set_layout (QtPlug *widget, gint layout);

G_END_DECLS

#endif /* _QT_PLUG_H_ */
