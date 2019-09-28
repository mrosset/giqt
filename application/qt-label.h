/*
 * qt-label.h
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

#ifndef __QT_LABEL_H__
#define __QT_LABEL_H__

#include <qt-widget.h>

G_BEGIN_DECLS

#define QT_TYPE_LABEL qt_label_get_type ()
G_DECLARE_FINAL_TYPE (QtLabel, qt_label, QT, LABEL, QtWidget)

QtLabel *qt_label_new (const char *label);

G_END_DECLS

#endif /* __QT_LABEL_H__ */
