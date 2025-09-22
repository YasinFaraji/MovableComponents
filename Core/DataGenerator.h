#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>

class DataGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id MEMBER m_id CONSTANT)
    Q_PROPERTY(int value READ value NOTIFY valueChanged)

  public:
    explicit DataGenerator(QObject* parent = nullptr);
    explicit DataGenerator(const QString& id, int msec, int min, int max, QObject* parent = nullptr);
    ~DataGenerator();

    int value() const;

    Q_INVOKABLE void startUpdates();
    Q_INVOKABLE void pauseUpdates();
    Q_INVOKABLE void resumeUpdates();

  signals:
    void valueChanged();

  private slots:
    void generateNewValue();

  private:
    QString m_id;
    int m_value;
    int m_msec;
    int m_min;
    int m_max;
    QTimer m_timer;
};

#endif // DATAGENERATOR_H
