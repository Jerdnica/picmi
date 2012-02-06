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


#ifndef STREAKITEM_H
#define STREAKITEM_H

#include <QGraphicsTextItem>

#include "src/logic/picmi.h"
#include "renderer.h"
#include "reloadableitem.h"

class StreakItem : public QGraphicsTextItem, public ReloadableItem
{
public:
    StreakItem(int x, int y, boost::shared_ptr<Picmi> game, QGraphicsItem *parent = 0);

    virtual void refresh() = 0;
    virtual void reload(const QSize &size) = 0;

protected:

    int fontSize(int tilesize) const;

    const boost::shared_ptr<Picmi> m_game;
    const int m_padding;
    const QString m_color_solved, m_color_unsolved;
    boost::shared_ptr<QFont> m_font;
};

class RowStreakItem : public StreakItem {
public:
    RowStreakItem(boost::shared_ptr<Picmi> game, int y, QGraphicsItem *parent = 0);

    void refresh();
    void reload(const QSize &size);
};

class ColStreakItem : public StreakItem {
public:
    ColStreakItem(boost::shared_ptr<Picmi> game, int x, QGraphicsItem *parent = 0);

    void refresh();
    void reload(const QSize &size);
};

#endif // STREAKITEM_H
