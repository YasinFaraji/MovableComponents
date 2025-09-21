#include "DataGenerator.h"
#include <QDebug>

DataGenerator::DataGenerator(QObject* parent)
    : QObject(parent)
    , m_id("")
    , m_value(0)
    , m_msec(0)
    , m_min(0)
    , m_max(0)
{
    connect(&m_timer, &QTimer::timeout, this, &DataGenerator::generateNewValue);
}

DataGenerator::DataGenerator(const QString& id, int msec, int min, int max, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_msec(msec)
    , m_min(min)
    , m_max(max)
{
    connect(&m_timer, &QTimer::timeout, this, &DataGenerator::generateNewValue);
    m_timer.setInterval(m_msec);
    m_value = QRandomGenerator::global()->bounded(m_min, m_max + 1);
}

DataGenerator::~DataGenerator()
{
    m_timer.stop();
}

int DataGenerator::value() const
{
    return m_value;
}

void DataGenerator::startUpdates()
{
    if (!m_timer.isActive())
    {
        m_timer.start();
    }
}

void DataGenerator::pauseUpdates()
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }
}

void DataGenerator::resumeUpdates()
{
    if (!m_timer.isActive())
    {
        m_timer.start();
    }
}

void DataGenerator::generateNewValue()
{
    m_value = QRandomGenerator::global()->bounded(m_min, m_max + 1);
    qDebug() << m_id << "value changed to" << m_value;
    emit valueChanged();
}
