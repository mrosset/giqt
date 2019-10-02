/*
 * qt-box.cpp
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

#include "qt-box.h"
#include "util.h"
#include <QLayout>
#include <QWidget>

typedef struct _QtBoxPrivate QtBoxPrivate;

struct _QtBoxPrivate
{
  QGridLayout *qinst;
};

struct _QtBox
{
  GtkContainer parent;
  QtBoxPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtBox, qt_box, QT_TYPE_WIDGET);

static void
qt_box_init (QtBox *self)
{
  self->priv = (QtBoxPrivate *)qt_box_get_instance_private (self);
  self->priv->qinst = new QGridLayout;
}

// void
// qt_box_add (GtkContainer *container, GtkWidget *widget)
// {
//   g_debug ("QtBox Add");
//   QWidget *parent = QT_BOX (container)->priv->qinst;
//   QWidget *child = QT_BOX (widget)->priv->qinst;
//   DispatchOnMainThread ([=] { child->setParent (parent); });
// }

void
qt_box_class_init (QtBoxClass *klass)
{
  // GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  // GtkContainerClass *container_class = GTK_CONTAINER_CLASS (klass);
  // container_class->add = qt_box_add;
}
