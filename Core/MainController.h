#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "Core/DataGenerator.h"
#include <QFile>
#include <QHash>
#include <QObject>
#include <QVariantList>

class MainController : public QObject
{
    Q_OBJECT

  public:
    explicit MainController(QObject* parent = nullptr);

    Q_INVOKABLE QVariantList qmlComponents() const;
    Q_INVOKABLE QVariantList dataGenerators() const;

  public slots:
    void startAllGenerators();
    void handleComponentPositionChanged(const QString& id, qreal xPos);

  private:
    void readConfigs();
    void processDataFile(const QString& dataFileName);
    std::vector<QString> getFilteredFileNamesFromDirectory(const QString& folderPath);

    const qreal m_windowWidth;
    const qreal m_halfWidth;
    QVariantList m_qmlConfigData;
    QHash<QString, DataGenerator*> m_dataGenerators;
    QHash<QString, QString> m_componentDataSourceMap;
};

#endif // MAINCONTROLLER_H
