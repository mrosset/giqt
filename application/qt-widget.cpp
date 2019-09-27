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
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

typedef struct _QtWidgetPrivate QtWidgetPrivate;

struct _QtWidgetPrivate
{
  QWidget *qinst;
};

struct _QtWidget
{
  GtkContainer parent;
  QtWidgetPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtWidget, qt_widget, GTK_TYPE_CONTAINER);

void
qt_widget_init (QtWidget *self)
{
  self->priv = (QtWidgetPrivate *)qt_widget_get_instance_private (self);
  self->priv->qinst = new QWidget;
}

QtWidget *
qt_widget_new (void)
{
  return (QtWidget *)g_object_new (QT_TYPE_WIDGET, NULL);
}

void
qt_widget_add (GtkContainer *container, GtkWidget *child)
{
  DispatchOnMainThread ([=] {
    QtWidget *self = QT_WIDGET (container);
    QGridLayout *layout = new QGridLayout (self->priv->qinst);
    QT_WIDGET (child)->priv->qinst->setStyleSheet ("background-color:black;");
    layout->addWidget (QT_WIDGET (child)->priv->qinst);
    // QLabel *label = new QLabel ("Hello GNU!", self->priv->qinst);
    // label->setAlignment (Qt::AlignCenter);
    // self->priv->qinst->setCentralWidget (label);
    // self->priv->qinst->show ();
  });
}

void
qt_widget_show (GtkWidget *widget)
{
  QtWidget *self = QT_WIDGET (widget);
  DispatchOnMainThread ([=] {
    // QLabel *label = new QLabel ("Hello GNU!", self->priv->qinst);
    // label->setAlignment (Qt::AlignCenter);
    // self->priv->qinst->setCentralWidget (label);
    self->priv->qinst->show ();
  });
}

static void
qt_widget_finalize (GObject *object)
{
  /* TODO: Add deinitalization code here */

  G_OBJECT_CLASS (qt_widget_parent_class)->finalize (object);
}

static void
qt_widget_class_init (QtWidgetClass *klass)
{
  g_debug ("CLASS_INIT");
  // GParamFlags rw = (GParamFlags)G_PARAM_READWRITE;
  // GParamFlags co = (GParamFlags)G_PARAM_CONSTRUCT_ONLY;
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  GtkContainerClass *container_class = GTK_CONTAINER_CLASS (klass);

  // G_OBJECT_CLASS (widget_class)->set_property = application_set_property;
  // G_OBJECT_CLASS (widget_class)->get_property = application_get_property;

  // obj_properties[PROP_APPLICATION] = g_param_spec_pointer (
  //     "application", "Application", "The Application used by the window",
  //     rw);

  // g_object_class_install_properties (G_OBJECT_CLASS (widget_class),
  //                                    N_PROPERTIES, obj_properties);
  G_OBJECT_CLASS (widget_class)->finalize = qt_widget_finalize;
  widget_class->show = qt_widget_show;
  container_class->add = qt_widget_add;
}
