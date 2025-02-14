Renderer::Renderer(QObject *parent)
{
    trend->formAlarms(StartTime)

    QVector<QList>> alarms = trend->pushAlarms();

    alarmsEngine->getAlarms(alarms);
}

AlarmsEngine::getAlarms(QVector<QList>>& alarms)
{
    this->alarms = alarms;
    sortAlarms();
}

void Renderer::incrementCursor()
{
    m_cursorTimeMark = QDateTime::fromMSecsSinceEpoch(m_cursorTimeMark.toMSecsSinceEpoch() + 1 * 60 * 1000);

    if(m_cursorTimeMark >= xLimitEnd)
    {
        m_cursorTimeMark = xLimitEnd;
        xLimitStart = xLimitEnd;
        xLimitEnd = xLimitStart.addSecs(60 * 60);

        trend->formHourOfTrend(xLimitStart);

        QVector<QPointF> hrSeries = trend->getTrendSeries(Params::parHR);
        QVector<QPointF> prSeries = trend->getTrendSeries(Params::parPR);
        QVector<QPointF> rrSeries = trend->getTrendSeries(Params::parRR);
        QVector<QPointF> t1Series = trend->getTrendSeries(Params::parT1);

        lines[0]->clearSeries();
        lines[1]->clearSeries();
        lines[2]->clearSeries();
        lines[3]->clearSeries();

        for(auto &point : hrSeries)
        {
            lines[0]->push(point);
        }

        for(auto &point : prSeries)
        {
            lines[1]->push(point);
        }

        for(auto &point : rrSeries)
        {
            lines[2]->push(point);
        }

        for(auto &point : t1Series)
        {
            point.ry() -= 10;
            lines[3]->push(point);
        }

        for(auto &chart : charts)
        {
            chart->updateSeries();

        }
        emit maxLimitChangesX(xLimitEnd);
        emit minLimitChangesX(xLimitStart);
    }

    emit cursorTimeMarkChanged(m_cursorTimeMark);
}