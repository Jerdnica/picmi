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

#include "highscores.h"

#include "constants.h"

HighScores::HighScores() : m_prefix("highscores")
{
    m_settings.reset(new QSettings(QSettings::IniFormat, QSettings::UserScope,
                       ORGANIZATION_NAME, "highscores"));

    m_size = m_settings->beginReadArray(m_prefix);
    for (int i = 0; i < m_size; i++) {
        boost::shared_ptr<HighScore> p(new HighScore(m_settings, i));
        m_scores.push_back(p);
    }
    m_settings->endArray();
}

void HighScores::add(boost::shared_ptr<HighScore> score) {
    m_scores.push_back(score);
    m_settings->beginWriteArray(m_prefix);
    m_settings->setArrayIndex(m_size);
    score->save(m_settings);
    m_settings->endArray();
    m_size++;
}

QList<boost::shared_ptr<HighScore> > HighScores::scoresInCategory(int h, int w, double density, bool no_hints_mode) const {
    QList<boost::shared_ptr<HighScore> > scores;
    for (int i = 0; i < m_scores.size(); i++) {
        if (m_scores[i]->boxDensity() == density &&
            m_scores[i]->noHintsMode() == no_hints_mode &&
            m_scores[i]->height() == h &&
            m_scores[i]->width() == w) {
            scores.push_back(m_scores[i]);
        }
    }
    return scores;
}

HighScore::HighScore(boost::shared_ptr<QSettings> settings, int index)
{
    initKeys();

    settings->setArrayIndex(index);

    m_datetime = settings->value(m_keys[DateTime]).toDateTime();
    m_width = settings->value(m_keys[Width]).toInt();
    m_height = settings->value(m_keys[Height]).toInt();
    m_played_seconds = settings->value(m_keys[PlayedSeconds]).toInt();
    m_box_density = settings->value(m_keys[BoxDensity]).toDouble();
    m_no_hints_mode = settings->value(m_keys[NoHintsMode]).toBool();
}

void HighScore::initKeys() {
    m_keys << "datetime"
           << "width"
           << "height"
           << "played_seconds"
           << "box_density"
           << "no_hints_mode";
}

HighScore::HighScore(const Settings &settings,
                     QDateTime datetime, int played_seconds)
{
    initKeys();

    m_datetime = datetime;
    m_width = settings.width();
    m_height = settings.height();
    m_played_seconds = played_seconds;
    m_box_density = settings.boxDensity();
    m_no_hints_mode = settings.noHintsMode();
}

void HighScore::save(boost::shared_ptr<QSettings> settings) const {
    settings->setValue(m_keys[DateTime], m_datetime);
    settings->setValue(m_keys[Width], m_width);
    settings->setValue(m_keys[Height], m_height);
    settings->setValue(m_keys[PlayedSeconds], m_played_seconds);
    settings->setValue(m_keys[BoxDensity], m_box_density);
    settings->setValue(m_keys[NoHintsMode], m_no_hints_mode);
    settings->sync();
}
