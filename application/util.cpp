#include "util.h"
#include <QApplication>
#include <QTimer>

void
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
