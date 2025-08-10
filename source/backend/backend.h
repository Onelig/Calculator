#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtQml/qqml.h>
#include <QGuiApplication>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QStringList historyList READ getHistoryList NOTIFY historyListChanged)

public:
    enum RemoveMode
    {
        REMOVE_ELEM,
        REMOVE_STR,
        REMOVE_ALL
    };
    Q_ENUM(RemoveMode)

public: // for Calculator Page
    explicit Backend(QObject *parent = nullptr);
    Q_INVOKABLE void remove(RemoveMode mode);
    Q_INVOKABLE void addDigit(const QChar& digit);
    Q_INVOKABLE void addOper(const QChar& oper); // Just PLUS, MINUS, MULTIPLY, DIVIDE
    Q_INVOKABLE void changeSign();
    Q_INVOKABLE void addPoint();
    Q_INVOKABLE void addRoot();
    Q_INVOKABLE void addPercent();
    Q_INVOKABLE void addBracket(bool isOpen);
    Q_INVOKABLE void getResult();


public:// for History Page
    QStringList getHistoryList();

signals:
    void strUpdated(const QString &newStr);
    void histUpdated(const QString& newHist);

    void historyListChanged();
    void targetButton(const QString& buttonName);
protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    QString str;
    int lr_brackets = 0; // left and right button
    QStringList history;

    void ChangeSignASign(int index);
    void CorrectChop();
    void ifHavePrevError();
};

#endif // BACKEND_H
