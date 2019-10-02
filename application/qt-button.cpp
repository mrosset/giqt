/*
 * qt-button.cpp
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

#include "qt-button.h"
#include <QPushButton>
#include <QWidget>

enum
{
  CLICKED = 1,
  N_SIGNALS
};

static guint button_signals[N_SIGNALS] = {};

typedef struct _QtButtonPrivate QtButtonPrivate;

struct _QtButtonPrivate
{
  QWidget *qinst;
};

struct _QtButton
{
  GtkContainer parent;
  QtButtonPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtButton, qt_button, QT_TYPE_WIDGET);

QtButton *
qt_button_new (void)
{
  return (QtButton *)g_object_new (QT_TYPE_BUTTON, NULL);
}

static void
qt_button_init (QtButton *self)
{
  self->priv = (QtButtonPrivate *)qt_button_get_instance_private (self);

  QPushButton *button = new QPushButton ("Click Here");
  QObject::connect (button, &QPushButton::clicked, [=]() {
    g_signal_emit (self, button_signals[CLICKED], 0);
  });

  self->priv->qinst = button;
}

void
qt_button_class_init (QtButtonClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  GSignalFlags flags = G_SIGNAL_RUN_LAST;
  /* | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS; */

  button_signals[CLICKED]
      = g_signal_newv ("clicked", G_TYPE_FROM_CLASS (object_class), flags,
                       NULL, NULL, NULL, NULL, G_TYPE_NONE, 0, NULL);
}
