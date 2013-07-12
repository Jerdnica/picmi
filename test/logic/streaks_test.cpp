#include "streaks_test.h"

#include <QTest>

#include "streaks.h"

QTEST_MAIN(StreaksTest)

#define STREAK_TEST(map, state, expected) do { \
    QSharedPointer<Streaks> s = generateStreaks(map, state); \
    if (!s) { \
        QFAIL("Streak generation failed."); \
    } \
    QVector<QSharedPointer<Streaks::StreakElement> > row = s->getRowStreak(0); \
    QVERIFY(streakEquals(row, expected)); \
} while (false);

/**
 * Generates a Streaks instance from the given string representations
 * of map and state. A map string consists of '.' and 'b' chars, representing
 * respectively Nothing and Box cells. A state string consists of '.', 'b' and
 * 'x' chars (with 'x' representing cross cells). If the board has more than
 * one row, each line is terminated by '\n'.
 */
static QSharedPointer<Streaks>
generateStreaks(const QString &map, const QString &state)
{
    if (map.size() != state.size()) {
        return QSharedPointer<Streaks>();
    }

    /* Generate the map. */

    QList<Board::State> ss;
    for (int i = 0; i < map.size(); i++) {
        switch (map[i].toAscii()) {
        case '.': /* Nothing. */
            ss.append(Board::Nothing);
            break;
        case 'b': /* Box. */
            ss.append(Board::Box);
            break;
        default:
            return QSharedPointer<Streaks>();
        }
    }

    QSharedPointer<BoardMap> mptr(new BoardMap(map.size(), 1, ss));

    /* Generate the state. */

    QSharedPointer<BoardState> sptr(new BoardState(state.size(), 1));

    for (int i = 0; i < state.size(); i++) {
        switch (state[i].toAscii()) {
        case '.': /* Nothing. */
            break;
        case 'b': /* Box. */
            sptr->set(i, 0, Board::Box);
            break;
        case 'x': /* Cross. */
            sptr->set(i, 0, Board::Cross);
            break;
        default:
            return QSharedPointer<Streaks>();
        }
    }

    return QSharedPointer<Streaks>(new Streaks(mptr, sptr));
}

/**
 * Compares the actual streak result against a string representing the
 * expected result. The string consists of 'x' and '.' characters representing,
 * respectively, solved and unsolved streaks.
 */
static bool
streakEquals(const QVector<QSharedPointer<Streaks::StreakElement> > &actual,
             const QString &expected)
{
    if (actual.size() != expected.size()) {
        QWARN("Actual size not equal to expected size.");
        return false;
    }

    QString actualString;

    for (int i = 0; i < expected.size(); i++) {
        if (actual[i]->solved) {
            actualString.append('x');
        } else {
            actualString.append('.');
        }
    }

    if (actualString == expected) {
        return true;
    }

    QString msg = "Result mismatch. Actual: " + actualString + ", Expected: " + expected;
    QWARN(msg.toAscii());

    return false;
}

void StreaksTest::testSanity()
{
    QSharedPointer<Streaks> s = generateStreaks("....b", "xxxxb");

    QCOMPARE(1, 1);
}

void StreaksTest::test00()
{
    /* Lifted from https://bugs.kde.org/show_bug.cgi?id=321842 */
    STREAK_TEST("bb.b.bbbb.bbb.b",
                "bbxbxbb.bxbbbxb",
                "xx.xx");
}

}
