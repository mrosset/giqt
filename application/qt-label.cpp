/*
 * qt-label.cpp
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

#include "qt-label.h"
#include "util.h"
#include <QDebug>
#include <QLabel>

enum
{
  PROP_LABEL = 1,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = {
  NULL,
};

typedef struct _QtLabelPrivate QtLabelPrivate;

struct _QtLabelPrivate
{
  QLabel *qinst;
};

struct _QtLabel
{
  GtkContainer parent;
  QtLabelPrivate *priv;
};

G_DEFINE_TYPE_WITH_PRIVATE (QtLabel, qt_label, QT_TYPE_WIDGET);

static void
label_set_property (GObject *object, guint property_id, const GValue *value,
                    GParamSpec *pspec)
{
  QtLabel *self = QT_LABEL (object);
  char *label = NULL;
  switch (property_id)
    {
    case PROP_LABEL:
      label = g_value_dup_string (value);
      DispatchOnMainThread (
          [=] { self->priv->qinst->setText (QString (label)); });

      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
label_get_property (GObject *object, guint property_id, GValue *value,
                    GParamSpec *pspec)
{
  QtLabel *self = QT_LABEL (object);
  QString text = self->priv->qinst->text ();

  switch (property_id)
    {
    case PROP_LABEL:
      DispatchOnMainThread (
          [=] { g_value_set_string (value, text.toUtf8 ().constData ()); });
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
qt_label_init (QtLabel *self)
{
  self->priv = (QtLabelPrivate *)qt_label_get_instance_private (self);
  self->priv->qinst = new QLabel;
}

QtLabel *
qt_label_new (const char *label)
{
  return (QtLabel *)g_object_new (QT_TYPE_LABEL, "label", label, NULL);
}

static void
qt_label_finalize (GObject *gobject)
{
  g_signal_handlers_destroy (gobject);
  G_OBJECT_CLASS (qt_label_parent_class)->finalize (gobject);
}

static void
qt_label_class_init (QtLabelClass *klass)
{

  int flags = G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE;
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  G_OBJECT_CLASS (gobject_class)->set_property = label_set_property;
  G_OBJECT_CLASS (gobject_class)->get_property = label_get_property;

  obj_properties[PROP_LABEL] = g_param_spec_string (
      "label", "Label", "The text for the label", NULL, (GParamFlags)flags);

  g_object_class_install_properties (gobject_class, N_PROPERTIES,
                                     obj_properties);

  gobject_class->finalize = qt_label_finalize;
}
