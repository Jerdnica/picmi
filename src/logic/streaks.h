/* *************************************************************************
 *  Copyright 2012 Jakob Gruber <jakob.gruber@gmail.com>                   *
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

#ifndef STREAKS_H
#define STREAKS_H

#include <QVector>
#include <QSharedPointer>

#include "boardmap.h"
#include "boardstate.h"

struct Streak {
    int count;
    int begin, end;
};

/* Moved from streaks.cpp to work around QSharedPointer issues with forward declarations.
 * TODO: move this back once when Qt 5 is used. */
struct LineInfo {
    LineInfo(const QVector<Board::State> &l);

    QVector<Streak> streaks_regular;
    QVector<Streak> streaks_reversed;
};

class Streaks
{
public:
    struct StreakElement {
        int value;
        bool solved;
    };

    Streaks(QSharedPointer<BoardMap> map, QSharedPointer<BoardState> state);

    /* Updates streaks affected by changes to (x,y). */
    void update(int x, int y);

    /* Updates streaks, taking the entire board into account. */
    void update();

    /* Returns the request row/col streak. These contain the least information required by
       the frontend, which is (for each position within a streak): "which number is this",
       and "is this position solved" */
    QVector<QSharedPointer<Streaks::StreakElement> > getRowStreak(int y) const;
    QVector<QSharedPointer<Streaks::StreakElement> > getColStreak(int x) const;

private:

    void calcMapStreaks();


    QSharedPointer<BoardMap> m_map;
    QSharedPointer<BoardState> m_state;

    QVector<QVector<Streak> > m_map_row_streaks;
    QVector<QVector<Streak> > m_map_col_streaks;

    QVector<QSharedPointer<LineInfo> > m_state_row_streaks;
    QVector<QSharedPointer<LineInfo> > m_state_col_streaks;
};

#endif // STREAKS_H
