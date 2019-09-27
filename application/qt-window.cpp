/*
 * qt-window.c
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

#include "qt-window.h"
#include "qt-application.h"
#include "util.h"
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QWebEngineView>
#include <QtWebEngine>

enum
{
  PROP_APPLICATION = 1,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = {
  NULL,
};

typedef struct _QtWindowPrivate QtWindowPrivate;

struct _QtWindowPrivate
{
  QMainWindow *qinst;
  QtApplication *app;
  gboolean dispatch;
};

struct _QtWindow
{
  GtkWidget parent;
  QtWindowPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtWindow, qt_window, GTK_TYPE_WIDGET);

static void
application_set_property (GObject *object, guint property_id,
                          const GValue *value, GParamSpec *pspec)
{
  QtWindow *self = QT_WINDOW (object);
  switch (property_id)
    {
    case PROP_APPLICATION:
      self->priv->app = (QtApplication *)g_value_get_pointer (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
application_get_property (GObject *object, guint property_id, GValue *value,
                          GParamSpec *pspec)
{
  QtWindow *self = QT_WINDOW (object);

  switch (property_id)
    {
    case PROP_APPLICATION:
      g_value_set_pointer (value, self->priv->app);
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

QtWindow *
qt_window_new ()
{
  return (QtWindow *)g_object_new (QT_TYPE_WINDOW, NULL);
}

void
qt_window_init (QtWindow *self)
{
  g_debug ("INIT");
  self->priv = (QtWindowPrivate *)qt_window_get_instance_private (self);
  self->priv->qinst = new QMainWindow;
}

static void
DispatchOnMainThread (std::function<void()> callback)
{
  QTimer *timer = new QTimer ();
  timer->moveToThread (qApp->thread ());
  timer->setSingleShot (true);
  QObject::connect (timer, &QTimer::timeout, [=]() {
    callback ();
    timer->deleteLater ();
  });
  QMetaObject::invokeMethod (timer, "start", Qt::QueuedConnection,
                             Q_ARG (int, 0));
}

void
qt_window_show (GtkWidget *widget)
{
  QtWindow *self = QT_WINDOW (widget);
  DispatchOnMainThread ([=] {
    QLabel *label = new QLabel ("Hello GNU!", self->priv->qinst);
    label->setAlignment (Qt::AlignCenter);
    self->priv->qinst->setCentralWidget (label);
    self->priv->qinst->show ();
  });
}

static void
qt_window_finalize (GObject *object)
{
  /* TODO: Add deinitalization code here */

  G_OBJECT_CLASS (qt_window_parent_class)->finalize (object);
}

static void
qt_window_class_init (QtWindowClass *klass)
{
  g_debug ("CLASS_INIT");
  GParamFlags rw = (GParamFlags)G_PARAM_READWRITE;
  // GParamFlags co = (GParamFlags)G_PARAM_CONSTRUCT_ONLY;
  GtkWidgetClass *gtk_class = GTK_WIDGET_CLASS (klass);

  G_OBJECT_CLASS (gtk_class)->set_property = application_set_property;
  G_OBJECT_CLASS (gtk_class)->get_property = application_get_property;

  obj_properties[PROP_APPLICATION] = g_param_spec_pointer (
      "application", "Application", "The Application used by the window", rw);

  g_object_class_install_properties (G_OBJECT_CLASS (gtk_class), N_PROPERTIES,
                                     obj_properties);
  G_OBJECT_CLASS (gtk_class)->finalize = qt_window_finalize;
  gtk_class->show = qt_window_show;
}
