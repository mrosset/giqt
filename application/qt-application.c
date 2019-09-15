/*
 * qt-application.c
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

#include "qt-application.h"

struct _QtApplicationPrivate
{
};

G_DEFINE_TYPE (QtApplication, qt_application, G_TYPE_OBJECT);

static void
qt_application_init (QtApplication *qt_application)
{
  qt_application->priv = G_TYPE_INSTANCE_GET_PRIVATE (
      qt_application, QT_TYPE_APPLICATION, QtApplicationPrivate);

  /* TODO: Add initialization code here */
}

static void
qt_application_finalize (GObject *object)
{
  /* TODO: Add deinitalization code here */

  G_OBJECT_CLASS (qt_application_parent_class)->finalize (object);
}

static void
qt_application_class_init (QtApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (QtApplicationPrivate));

  object_class->finalize = qt_application_finalize;
}

const char *
qt_application_version ()
{
  return "0.0.1-alpha";
}
