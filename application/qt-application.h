/*
 * qt-application.h
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

#ifndef _QT_APPLICATION_H_
#define _QT_APPLICATION_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define QT_TYPE_APPLICATION (qt_application_get_type ())
#define QT_APPLICATION(obj)                                                   \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), QT_TYPE_APPLICATION, QtApplication))
#define QT_APPLICATION_CLASS(klass)                                           \
  (G_TYPE_CHECK_CLASS_CAST ((klass), QT_TYPE_APPLICATION, QtApplicationClass))
#define QT_IS_APPLICATION(obj)                                                \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), QT_TYPE_APPLICATION))
#define QT_IS_APPLICATION_CLASS(klass)                                        \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), QT_TYPE_APPLICATION))
#define QT_APPLICATION_GET_CLASS(obj)                                         \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), QT_TYPE_APPLICATION, QtApplicationClass))

typedef struct _QtApplicationClass QtApplicationClass;
typedef struct _QtApplication QtApplication;
typedef struct _QtApplicationPrivate QtApplicationPrivate;

struct _QtApplicationClass
{
  GObjectClass parent_class;
};

struct _QtApplication
{
  GObject parent_instance;

  QtApplicationPrivate *priv;
};

GType qt_application_get_type (void) G_GNUC_CONST;

G_END_DECLS

const char *qt_application_version ();

#endif /* _QT_APPLICATION_H_ */
