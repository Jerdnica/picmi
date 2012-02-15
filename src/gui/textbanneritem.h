/* *************************************************************************
 *  Copyright 2012 Jakob Gruber                                            *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 ************************************************************************* */


#ifndef PAUSEBANNERITEM_H
#define PAUSEBANNERITEM_H

#include <QGraphicsSimpleTextItem>
#include <QFont>
#include <QTime>

#include "reloadableitem.h"

class TextBannerItem : public QGraphicsSimpleTextItem, public ReloadableItem
{
public:
    TextBannerItem(QGraphicsItem *parent = 0);

    void reload(const QSize &size);

protected:
    boost::shared_ptr<QFont> m_font;
};

class TimeBannerItem : public TextBannerItem
{
public:
    TimeBannerItem(QGraphicsItem *parent = 0);

    void setTime(const QTime &time);
    void reload(const QSize &size);
};

class PauseBannerItem : public TextBannerItem
{
public:
    PauseBannerItem(QGraphicsItem *parent = 0);

    void reload(const QSize &size);
};

#endif // PAUSEBANNERITEM_H