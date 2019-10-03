/*
 * qt-line-edit.cpp
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

#include "qt-line-edit.h"
#include <QLineEdit>

struct _QtLineEditPrivate
{
  QLineEdit *qinst;
};

G_DEFINE_TYPE (QtLineEdit, qt_line_edit, QT_TYPE_WIDGET);

static void
qt_line_edit_init (QtLineEdit *self)
{
  QLineEdit *line_edit = new QLineEdit;
  // self->priv = (QtLineEditPrivate *)qt_line_edit_get_instance_private
  // (self);
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, QT_TYPE_LINE_EDIT,
                                            QtLineEditPrivate);
  self->priv->qinst = line_edit;
}

static void
qt_line_edit_finalize (GObject *object)
{
  G_OBJECT_CLASS (qt_line_edit_parent_class)->finalize (object);
}

static void
qt_line_edit_class_init (QtLineEditClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  // g_type_class_add_private (klass, sizeof (QtLineEditPrivate));

  object_class->finalize = qt_line_edit_finalize;
}
