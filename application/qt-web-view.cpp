/*
 * qt-web-view.cpp
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

#include "qt-web-view.h"
#include "util.h"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QtWebEngine>

int argc = 0;
char *argv[] = { NULL };

QApplication *default_app = NULL;

typedef struct _QtWebViewPrivate QtWebViewPrivate;

struct _QtWebViewPrivate
{
  QWebEngineView *qinst;
};

struct _QtWebView
{
  GObject parent;
  QtWebViewPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtWebView, qt_web_view, G_TYPE_OBJECT);

static void
qt_web_view_init (QtWebView *self)
{
  if (!default_app)
    {
      QCoreApplication::setAttribute (Qt::AA_EnableHighDpiScaling);
      default_app = new QApplication (argc, argv);
      QtWebEngine::initialize ();
    }

  self->priv = (QtWebViewPrivate *)qt_web_view_get_instance_private (self);

  QWebEngineView *view = new QWebEngineView;
  view->winId ();
  view->load (QUrl ("about://"));
  self->priv->qinst = view;
}

QtWebView *
qt_web_view_new (const long socket_id)
{
  QtWebView *self = (QtWebView *)g_object_new (QT_TYPE_WEB_VIEW, NULL);
  QWebEngineView *view = self->priv->qinst;
  QWindow *wlbl = view->windowHandle ();
  wlbl->setParent (QWindow::fromWinId (socket_id));
  view->show ();
  return self;
}

static void
qt_web_view_finalize (GObject *gobject)
{
  g_signal_handlers_destroy (gobject);
  G_OBJECT_CLASS (qt_web_view_parent_class)->finalize (gobject);
}

static void
qt_web_view_class_init (QtWebViewClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = qt_web_view_finalize;
}

void
qt_web_view_load_uri (QtWebView *self, const char *uri)
{
  g_print ("LOAD_URI\n");
  GMainContext *worker_context = g_main_context_new ();
  g_main_context_push_thread_default (worker_context);
  self->priv->qinst->load (QUrl (uri));
  g_main_context_pop_thread_default (worker_context);
}
