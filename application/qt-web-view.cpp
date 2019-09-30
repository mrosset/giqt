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
#include <QLabel>
#include <QWebEngineView>

typedef struct _QtWebViewPrivate QtWebViewPrivate;

struct _QtWebViewPrivate
{
  QWebEngineView *qinst;
};

struct _QtWebView
{
  GtkContainer parent;
  QtWebViewPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtWebView, qt_web_view, QT_TYPE_WIDGET);

static void
qt_web_view_init (QtWebView *self)
{
  self->priv = (QtWebViewPrivate *)qt_web_view_get_instance_private (self);
  // DispatchOnMainThread ([=] {
  self->priv->qinst = new QWebEngineView;
  // });
  // self->priv->qinst->load (QUrl ("http://gnu.org"));
}

QtWebView *
qt_web_view_new (void)
{
  return (QtWebView *)g_object_new (QT_TYPE_WEB_VIEW, NULL);
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
  self->priv->qinst->load (QUrl (uri));
}
