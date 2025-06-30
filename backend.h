#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum RemoveMode
    {
        REMOVE_ELEM,
        REMOVE_STR,
        REMOVE_ALL
    };
    Q_ENUM(RemoveMode)

public:
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void remove(RemoveMode mode);
    Q_INVOKABLE void addDigit(const QString& digit);
    Q_INVOKABLE void addOper(const QString& oper);

signals:
    void strUpdated(const QString &newStr);

private:
    QString str;
};

#endif // BACKEND_H
