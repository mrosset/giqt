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

#include "qt-plug.h"
#include "util.h"
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QWebEngineView>
#include <QWidget>
#include <QtWebEngine>

int argc = 0;
char *argv[] = { NULL };

QApplication *default_app = NULL; // new QApplication (argc, argv);

typedef struct _QtPlugPrivate QtPlugPrivate;

struct _QtPlugPrivate
{
  QWebEngineView *qinst;
  QGridLayout *layout;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtPlug, qt_plug, GTK_TYPE_BIN);

void
qt_plug_init (QtPlug *self)
{
  QWidget *widget = new QWidget;
  QGridLayout *layout = new QGridLayout (widget);

  layout->setRowStretch (0, 1);
  layout->setMargin (0);

  self->priv = (QtPlugPrivate *)qt_plug_get_instance_private (self);
  self->priv->qinst = widget;
  self->priv->layout = layout;
}

QtPlug *
qt_plug_new (void)
{
  return (QtPlug *)g_object_new (QT_TYPE_WIDGET, NULL);
}

void
qt_plug_add (GtkContainer *container, GtkWidget *widget)
{
  g_debug ("QtPlug Add");
  QGridLayout *layout = QT_PLUG (container)->priv->layout;
  QWidget *child = QT_PLUG (widget)->priv->qinst;

  layout->addWidget (child);
}

void
qt_plug_set_parent (QtPlug *widget, QtPlug *parent)
{
  QWidget *qparent = QT_PLUG (parent)->priv->qinst;
  QWidget *qchild = QT_PLUG (widget)->priv->qinst;
  DispatchOnMainThread ([=] { qchild->setParent (qparent); });
}

void
qt_plug_set_layout (QtPlug *widget, gint layout)
{
  QWidget *qwidget = widget->priv->qinst;
  if (layout == 0)
    {
      qwidget->setLayout (new QGridLayout);
    }
}

void
qt_plug_fill_parent (GtkContainer *container, GtkWidget *widget)
{
  QWidget *parent = QT_PLUG (container)->priv->qinst;
  QWidget *child = QT_PLUG (widget)->priv->qinst;

  DispatchOnMainThread ([=] {
    QGridLayout *layout = new QGridLayout (parent);
    layout->addWidget (child, 0, 0, 1, 1);
    layout->setMargin (0);
  });
}

void
qt_plug_show (GtkWidget *widget)
{
  DispatchOnMainThread ([=] {
    QtPlug *self = QT_PLUG (widget);
    self->priv->qinst->show ();
  });
}

static void
qt_plug_finalize (GObject *object)
{
  G_OBJECT_CLASS (qt_plug_parent_class)->finalize (object);
}

// static void
// qt_plug_grab_focus (GtkWidget *widget)
// {
//   QT_PLUG (widget)->priv->qinst->setFocus ();
// }

static void
qt_plug_class_init (QtPlugClass *klass)
{
  g_debug ("QT_PLUG_CLASS_INIT");

  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  // GtkContainerClass *container_class = GTK_CONTAINER_CLASS (klass);

  G_OBJECT_CLASS (widget_class)->finalize = qt_plug_finalize;
  // widget_class->show = qt_plug_show;
  // widget_class->grab_focus = qt_plug_grab_focus;
  // container_class->add = qt_plug_add;
}
