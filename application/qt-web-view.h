#ifndef __QT_WEB_VIEW_H__
#define __QT_WEB_VIEW_H__

#include "qt-widget.h"

G_BEGIN_DECLS

#define QT_TYPE_WEB_VIEW (qt_web_view_get_type ())
G_DECLARE_FINAL_TYPE (QtWebView, qt_web_view, QT, WEB_VIEW, QtWidget)

QtWebView *qt_web_view_new (void);

void qt_web_view_load_uri (QtWebView *self, const char *uri);

G_END_DECLS

#endif /* __QT_WEB_VIEW_H__ */
