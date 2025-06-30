#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{}

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

void Backend::addDigit(const QString &digit)
{
    str += digit;
    emit strUpdated(str);
}

void Backend::addOper(const QString &oper)
{
    if (str.back().isSymbol() && !(oper == QStringLiteral("\u2212") && str.back() != QChar(0x2212) && str.back() != QChar('+'))) // '-'
    {
        if (str.size() >= 2 && !str[str.size() - 2].isSymbol())
            str.back() = oper.front();
    }
    else
        str += oper;

    emit strUpdated(str);
}

void Backend::changeSign()
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
    emit strUpdated(str);
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
