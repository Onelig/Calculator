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
        auto iter = std::find_if(str.rbegin(), str.rend(), [](QChar a){ return a.isSymbol(); });
        if (iter == str.rend())
            str.clear();
        else
        {
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
