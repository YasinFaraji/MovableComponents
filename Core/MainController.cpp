#include "Core/MainController.h"

#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

MainController::MainController(QObject* parent)
    : QObject(parent)
    , m_windowWidth(880.0)
    , m_halfWidth(m_windowWidth / 2.0)
{
    readConfigs();
}

void MainController::readConfigs()
{
    auto fileNames = getFilteredFileNamesFromDirectory(":/assets/config");
    for (const auto fileName : fileNames)
    {
        processDataFile(fileName);
    }

    QFile qmlFile(":/assets/config/qml_config.json");
    if (qmlFile.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(qmlFile.readAll());
        m_qmlConfigData = doc.array().toVariantList();

        for (const QVariant& variant : m_qmlConfigData)
        {
            QVariantMap map = variant.toMap();
            m_componentDataSourceMap[map["id"].toString()] = map["dataSource"].toString();
        }
        qmlFile.close();
    }
    else
    {
        qWarning() << "Could not open QML config file.";
    }
}

void MainController::processDataFile(const QString& dataFileName)
{
    QFile dataFile(dataFileName);
    if (!dataFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Could not open data config file:" << dataFileName;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(dataFile.readAll());
    QJsonArray dataArray = doc.array();
    for (const QJsonValue& value : dataArray)
    {
        QJsonObject obj = value.toObject();
        QString id = obj["id"].toString();
        int msec = obj["msec"].toInt();
        int min = obj["min"].toInt();
        int max = obj["max"].toInt();
        m_dataGenerators[id] = new DataGenerator(id, msec, min, max, this);
    }
    dataFile.close();
}

std::vector<QString> MainController::getFilteredFileNamesFromDirectory(const QString& folderPath)
{
    std::vector<QString> fileNames;
    QDir directory(folderPath);

    if (!directory.exists())
    {
        qWarning("Directory does not exist.");
        return fileNames;
    }

    QRegularExpression regex("^data_config_\\d+\\.json$");

    QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo& fileInfo : fileInfoList)
    {
        if (regex.match(fileInfo.fileName()).hasMatch())
        {
            fileNames.push_back(":/assets/config/" + fileInfo.fileName());
        }
    }

    return fileNames;
}

QVariantList MainController::qmlComponents() const
{
    return m_qmlConfigData;
}

QVariantList MainController::dataGenerators() const
{
    QVariantList list;
    for (DataGenerator* gen : m_dataGenerators.values())
    {
        list << QVariant::fromValue(gen);
    }
    return list;
}

void MainController::startAllGenerators()
{
    for (DataGenerator* gen : m_dataGenerators.values())
    {
        gen->startUpdates();
    }
}

void MainController::handleComponentPositionChanged(const QString& id, qreal xPos)
{
    QString dataSourceId = m_componentDataSourceMap.value(id);
    DataGenerator* generator = m_dataGenerators.value(dataSourceId);

    if (generator)
    {
        if (xPos > m_halfWidth)
        {
            generator->pauseUpdates();
        }
        else
        {
            generator->resumeUpdates();
        }
    }
}
