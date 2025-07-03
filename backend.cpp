#include "backend.h"
#include <QKeyEvent>
#include <QRegularExpression>

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    qApp->installEventFilter(this);
}

void Backend::remove(RemoveMode mode)
{
    switch (mode)
    {
    case REMOVE_ELEM:
        if (!str.isEmpty())
            str.chop(1);
        break;
    case REMOVE_ALL:
        str.clear();
        break;
    case REMOVE_STR:
    {
        auto iter = std::find_if(str.rbegin(), str.rend(), [](const QChar& a){ return a.isSymbol(); });
        if (iter == str.rend())
            str.clear();
        else
        {
            if ((iter + 1)->isSymbol())
                ++iter;
            int index = iter.base() - 1 - str.begin();
            str.remove(index, str.size() - index);
        }
        break;
    }
    }

    emit strUpdated(str);
}

void Backend::addElem(const QChar &elem_)
{
    if (elem_.isDigit())
        addDigit(elem_);

    else if (elem_.isSymbol())
        addOper(elem_);
}

void Backend::addDigit(const QChar &digit)
{
    str += digit;
    emit strUpdated(str);
}

void Backend::addOper(const QChar &oper)
{
    if (!str.isEmpty())
    {
        if(str.back() == QChar('.'))
            str.chop(1);

        if (str.back().isSymbol() && !(oper == QChar(0x2212) && str.back() != QChar(0x2212) && str.back() != QChar('+'))) // '-'
        {
            if (str.size() >= 2 && !str[str.size() - 2].isSymbol())
                str.back() = oper;
        }
        else
            str += oper;
    }
    else if (oper == QChar(0x2212))
        str = QChar(0x2212);


    emit strUpdated(str);
}

void Backend::changeSign()
{
    if (!str.isEmpty())
    {
        if (str.back().isSymbol())
            ChangeSignASign(str.size() - 1);

        else
        {
            auto iter = std::find_if(str.rbegin(), str.rend(), [](const QChar& a){ return a.isSymbol(); });
            if (iter == str.rend())
                str.prepend(QChar(0x2212));

            else
                ChangeSignASign(iter.base() - 1 - str.begin());
        }
    }

    emit strUpdated(str);
}

void Backend::addPoint()
{
    if (!str.isEmpty())
    {
        bool pinStr = str.rbegin()->isSymbol();

        if (!pinStr)
        {
            for (auto iter = str.rbegin(), rend = str.rend(); iter != rend; ++iter)
            {
                if (iter->isSymbol())
                    break;

                else if (*iter == QChar('.'))
                {
                    pinStr = true;
                   break;
                }
            }

            if (!pinStr)
                str.push_back('.');
        }
    }

    emit strUpdated(str);
}

bool Backend::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();
        if (keyEvent->text().contains(QRegularExpression("[0-9]")))
            addDigit(keyEvent->text().back());
        else if (key == Qt::Key_Minus) // '-'
            addOper(QChar(0x2212));
        else if (key == Qt::Key_Asterisk) // '*'
            addOper(QChar(0x00D7));
        else if (key  == Qt::Key_Slash) // '/'
            addOper(QChar(0x00F7));
        else if (key == Qt::Key_Plus)
            addOper('+');
        else if (key == Qt::Key_Period)
            addPoint();
        else if (key == Qt::Key_Backspace && keyEvent->modifiers() & Qt::ControlModifier) // remove str
            remove(REMOVE_STR);
        else if (key == Qt::Key_Backspace) // remove one element
            remove(REMOVE_ELEM);

        return true;
    }

    return false;
}

void Backend::ChangeSignASign(int index)
{
    if (str[index] == QChar(0x2212)) // str[index] == '-'
    {
        if ((index >= 1 && str[index - 1].isSymbol()) || index < 1)
            str.remove(index, 1);
        else
            str[index] = QChar('+');
    }
    else if (str[index] == QChar('+')) // str[index] == '+'
        str[index] = QChar(0x2212); // '-'

    else
        str.insert(index + 1, QChar(0x2212));
}
