/*
 * qt-widget.cpp
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

#include "qt-widget.h"
#include "util.h"
#include <QLabel>
#include <QLayout>
#include <QWidget>

typedef struct _QtWidgetPrivate QtWidgetPrivate;

struct _QtWidgetPrivate
{
  QWidget *qinst;
  QGridLayout *layout;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtWidget, qt_widget, GTK_TYPE_CONTAINER);

void
qt_widget_init (QtWidget *self)
{
  QWidget *widget = new QWidget;
  QGridLayout *layout = new QGridLayout (widget);

  layout->setRowStretch (0, 1);
  layout->setMargin (0);

  self->priv = (QtWidgetPrivate *)qt_widget_get_instance_private (self);
  self->priv->qinst = widget;
  self->priv->layout = layout;
}

QtWidget *
qt_widget_new (void)
{
  return (QtWidget *)g_object_new (QT_TYPE_WIDGET, NULL);
}

void
qt_widget_add (GtkContainer *container, GtkWidget *widget)
{
  g_debug ("QtWidget Add");
  QGridLayout *layout = QT_WIDGET (container)->priv->layout;
  QWidget *child = QT_WIDGET (widget)->priv->qinst;

  layout->addWidget (child);
}

void
qt_widget_set_parent (QtWidget *widget, QtWidget *parent)
{
  QWidget *qparent = QT_WIDGET (parent)->priv->qinst;
  QWidget *qchild = QT_WIDGET (widget)->priv->qinst;
  DispatchOnMainThread ([=] { qchild->setParent (qparent); });
}

void
qt_widget_set_layout (QtWidget *widget, gint layout)
{
  QWidget *qwidget = widget->priv->qinst;
  if (layout == 0)
    {
      qwidget->setLayout (new QGridLayout);
    }
}

void
qt_widget_fill_parent (GtkContainer *container, GtkWidget *widget)
{
  QWidget *parent = QT_WIDGET (container)->priv->qinst;
  QWidget *child = QT_WIDGET (widget)->priv->qinst;

  DispatchOnMainThread ([=] {
    QGridLayout *layout = new QGridLayout (parent);
    layout->addWidget (child, 0, 0, 1, 1);
    layout->setMargin (0);
  });
}

void
qt_widget_show (GtkWidget *widget)
{
  DispatchOnMainThread ([=] {
    QtWidget *self = QT_WIDGET (widget);
    self->priv->qinst->show ();
  });
}

static void
qt_widget_finalize (GObject *object)
{
  G_OBJECT_CLASS (qt_widget_parent_class)->finalize (object);
}

static void
qt_widget_class_init (QtWidgetClass *klass)
{
  g_debug ("QT_WIDGET_CLASS_INIT");

  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  GtkContainerClass *container_class = GTK_CONTAINER_CLASS (klass);

  G_OBJECT_CLASS (widget_class)->finalize = qt_widget_finalize;
  widget_class->show = qt_widget_show;
  container_class->add = qt_widget_add;
}
