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
#include "../config.h"

typedef struct _QtApplicationPrivate QtApplicationPrivate;

struct _QtApplicationPrivate
{
  const char *version;
};

struct _QtApplication
{
  GObject parent;
  QtApplicationPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtApplication, qt_application, G_TYPE_APPLICATION);

QtApplication *
qt_application_new ()
{
  return g_object_new (QT_TYPE_APPLICATION, NULL);
}

static void
qt_application_init (QtApplication *self)
{
  self->priv = qt_application_get_instance_private (self);
  self->priv->version = VERSION;
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

  object_class->finalize = qt_application_finalize;
}

const char *
qt_application_version (QtApplication *self)
{
  return self->priv->version;
}
