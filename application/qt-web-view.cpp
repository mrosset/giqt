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
