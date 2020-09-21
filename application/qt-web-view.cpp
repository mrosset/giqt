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

typedef enum
{
  PROP_WINDOW_ID = 1,
  N_PROPS
} QtWebViewProperty;

static GParamSpec *qt_web_view_properties[N_PROPS] = {
  NULL,
};

int argc = 0;
char *argv[] = { NULL };

QApplication *default_app = NULL;

typedef struct _QtWebViewPrivate QtWebViewPrivate;

struct _QtWebViewPrivate
{
  QWebEngineView *qinst;
  guint window_id;
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
      QCoreApplication::setAttribute (Qt::AA_ShareOpenGLContexts);
      default_app = new QApplication (argc, argv);
      QtWebEngine::initialize ();
    }
  self->priv = (QtWebViewPrivate *)qt_web_view_get_instance_private (self);
  self->priv->qinst = new QWebEngineView;
  self->priv->qinst->winId ();
}

QtWebView *
qt_web_view_new (const long socket_id)
{
  return (QtWebView *)g_object_new (QT_TYPE_WEB_VIEW, "window-id", socket_id);
}

static void
qt_web_view_finalize (GObject *gobject)
{
  g_signal_handlers_destroy (gobject);
  G_OBJECT_CLASS (qt_web_view_parent_class)->finalize (gobject);
}

void
qt_web_view_set_id (QtWebView *self, guint window_id)
{
  self->priv->window_id = window_id;
  g_object_notify_by_pspec (G_OBJECT (self),
                            qt_web_view_properties[PROP_WINDOW_ID]);
  QWindow *wlbl = self->priv->qinst->windowHandle ();
  wlbl->setParent (QWindow::fromWinId (self->priv->window_id));
}

guint
qt_web_view_get_id (QtWebView *self)
{
  QWebEngineView *view = self->priv->qinst;
  qInfo () << "ID" << view->winId ();
  return view->winId ();
}

static void
qt_web_view_set_property (GObject *object, guint property_id,
                          const GValue *value, GParamSpec *pspec)
{
  QtWebView *self = QT_WEB_VIEW (object);

  switch ((QtWebViewProperty)property_id)
    {

    case PROP_WINDOW_ID:
      qt_web_view_set_id (self, g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
qt_web_view_get_property (GObject *object, guint property_id, GValue *value,
                          GParamSpec *pspec)
{

  QtWebView *self = QT_WEB_VIEW (object);

  QtWebViewPrivate *priv
      = (QtWebViewPrivate *)qt_web_view_get_instance_private (self);

  switch ((QtWebViewProperty)property_id)
    {
    case PROP_WINDOW_ID:
      g_value_set_uint (value, priv->window_id);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
qt_web_view_class_init (QtWebViewClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = qt_web_view_finalize;
  gobject_class->set_property = qt_web_view_set_property;
  gobject_class->get_property = qt_web_view_get_property;

  // clang-format off
  qt_web_view_properties[PROP_WINDOW_ID] =
    g_param_spec_uint ("window-id",
                       "WindowID",
                       "GtkSocket id to use",
                       0,
                       G_MAXINT,
                       0,
                       G_PARAM_READWRITE);
  // clang-format on

  g_object_class_install_properties (gobject_class, N_PROPS,
                                     qt_web_view_properties);
}

void
qt_web_view_show (QtWebView *self)
{
  self->priv->qinst->show ();
}

void
qt_web_view_reload (QtWebView *self)
{
  self->priv->qinst->reload ();
  self->priv->qinst->show ();
}

void
qt_web_view_load_uri (QtWebView *self, const char *uri)
{
  self->priv->qinst->load (QUrl (uri));
  qt_web_view_show (self);
}
