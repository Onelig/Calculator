#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include <QGuiApplication>

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
    Q_INVOKABLE void addDigit(const QChar& digit);
    Q_INVOKABLE void addOper(const QChar& oper);
    Q_INVOKABLE void changeSign();
    Q_INVOKABLE void addPoint();
    Q_INVOKABLE void addRoot();
    Q_INVOKABLE void addBracket(bool isOpen);
    Q_INVOKABLE void addPercent();

signals:
    void strUpdated(const QString &newStr);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    QString str;
    void ChangeSignASign(int index);

};

#endif // BACKEND_H
