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
#include "qt-window.h"
#include "util.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QWebEngineView>

int argc = 0;
char *argv[] = { NULL };

QApplication *default_app = NULL;

typedef struct _QtApplicationPrivate QtApplicationPrivate;

struct _QtApplicationPrivate
{
  QApplication *qinst;
};

struct _QtApplication
{
  GApplication parent;
  QtApplicationPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtApplication, qt_application, G_TYPE_APPLICATION);

QtApplication *
qt_application_new ()
{
  return (QtApplication *)g_object_new (
      QT_TYPE_APPLICATION, "application-id", "org.unknown", "flags",
      G_APPLICATION_HANDLES_OPEN | G_APPLICATION_CAN_OVERRIDE_APP_ID, NULL);
}

int
qt_application_start (QtApplication *self)
{
  char *argv[] = { NULL };
  return g_application_run (G_APPLICATION (self), 0, argv);
}

static void
startup (GApplication *application, gpointer user_data)
{
  g_debug ("STARTUP");
  DispatchOnMainThread ([=] { default_app->exec (); });
  g_debug ("RETURN from STARTUP");
}

static void
activate (QtApplication *self, gpointer user_data)
{
  g_debug ("ACTIVATE");
  g_debug ("RETURN from ACTIVATE");
}

static void
qt_application_init (QtApplication *self)
{
  if (!default_app)
    {
      default_app = new QApplication (argc, argv);
    }
  self->priv
      = (QtApplicationPrivate *)qt_application_get_instance_private (self);

  g_signal_connect (self, "startup", G_CALLBACK (startup), NULL);
  g_signal_connect (self, "activate", G_CALLBACK (activate), NULL);

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

gpointer
qt_application_get_app (QtApplication *self)
{
  return (gpointer)self->priv->qinst;
}

const char *
qt_application_version (QtApplication *self)
{
  return VERSION;
}

int
qt_major_version (void)
{
  return QT_VERSION_MAJOR;
}

const char *
qt_version (void)
{
  return QT_VERSION_STR;
}

void
qt_exec ()
{
  qDebug () << "Current Threaad" << QThread::currentThreadId ();
  qDebug () << "App Thread"
            << QApplication::instance ()->thread ()->currentThreadId ();
  qDebug () << "Bin" << qApp->thread ()->currentThreadId ();
  // QMainWindow win;
  // qDebug () << "Win" << win.thread ()->currentThreadId ();
  // win.show ();
  default_app->exec ();
  // exit (1);
  // qDebug () << QThread::currentThreadId ();
}
