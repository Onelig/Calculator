#include "backend.h"
#include <QKeyEvent>
#include <QRegularExpression>
#include "symbols.h"
#include "evaluator.h"

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
            CorrectChop();

        break;

    case REMOVE_ALL:
        lr_brackets = 0;
        str.clear();
        break;

    case REMOVE_STR:
    {
        auto iter = std::find_if(str.rbegin(), str.rend(), [this](const QChar& a)
                                {
                                    if      (a == LPAREN) lr_brackets--;
                                    else if (a == RPAREN) lr_brackets++;
                                    return a != DOT && isSymbol(a);
                                });
        if (iter == str.rend())
        {
            lr_brackets = 0;
            str.clear();
        }
        else
        {
            auto nextIter = std::next(iter);
            while (nextIter != str.rend() && (*nextIter) != DOT && isSymbol(*nextIter))
            {
                iter = nextIter++;
                if      (*(iter) == LPAREN) lr_brackets--;
                else if (*(iter) == RPAREN) lr_brackets++;
            }
            int index = iter.base() - 1 - str.begin();
            str.remove(index, str.size() - index);
        }

        break;
    }
    }

    emit strUpdated(str);
}

void Backend::addDigit(const QChar &digit)
{
    ifHavePrevError();
    bool allow = true;

    if (!str.isEmpty())
    {
        if (str == "0")
        {
            if (digit == QChar('0'))
                allow = false;
            else
                str.chop(1);
        }
        else if (str.back() == QChar('0') && str.size() > 1)
        {
            QChar prevElem = str[str.size() - 2];
            if (prevElem != DOT && isSymbol(prevElem))
            {
                if (digit == QChar('0'))
                    allow = false;
                else
                    str.chop(1);
            }
        }
    }

    if (allow)
        str += digit;

    emit strUpdated(str);
}

void Backend::addOper(const QChar &oper)
{
    ifHavePrevError();
    if (!str.isEmpty())
    {
        if (nonBOperatorFollowChars.indexOf(str.back()) != -1)
        {
            if (oper == MINUS && (str.back() == ROOT || str.back() == LPAREN || str.back() == DIVIDE || str.back() == MULTIPLY))
            {
                str.push_back(MINUS);
            }
            else if (str.size() >= 2 && nonBOperatorFollowChars.indexOf(str[str.size() - 2]) != -1)
            {
                if (oper == PLUS && (str[str.size() - 2] == DIVIDE || str[str.size() - 2] == MULTIPLY))
                    CorrectChop();
            }
            else if (str.size() >= 2)
            {
                CorrectChop();
                str.push_back(oper);
            }
        }
        else
            str.push_back(oper);
    }
    else if (oper == MINUS)
        str = MINUS;

    emit strUpdated(str);
}

void Backend::changeSign()
{
    ifHavePrevError();

    if (!str.isEmpty())
    {
        auto iter = std::find_if(str.rbegin(), str.rend(), [this](const QChar& a){ return a != DOT && isSymbol(a); });
        if (iter == str.rend())
            str.prepend(MINUS);

        else
            ChangeSignASign(std::distance(str.begin(), iter.base()) - 1);
    }

    emit strUpdated(str);
}

void Backend::addPoint()
{
    ifHavePrevError();
 
    if (!str.isEmpty())
    {
        bool issymbol = isSymbol(str.back());

        if (!issymbol)
        {
            for (auto iter = str.rbegin(), rend = str.rend(); iter != rend; ++iter)
            {
                if (*iter == DOT)
                {
                    issymbol = true;
                    break;
                }
                else if (isSymbol(*iter))
                    break;
            }

            if (!issymbol)
                str.push_back(DOT);
        }
        else
        {
            str += QString('0') + DOT;
        }
    }
    else
        str += QString('0') + DOT;

    emit strUpdated(str);
}

void Backend::addRoot()
{
    ifHavePrevError();

    if (!str.isEmpty() && str.back() == DOT)
        str.chop(1);

    str.push_back(ROOT);
    emit strUpdated(str);
}

void Backend::addPercent()
{
    ifHavePrevError();

    if (!str.isEmpty())
    {
        bool isLastSym = isSymbol(str.back());

        bool isAddPercent = !isLastSym;
        if (isLastSym)
        {
            if (str.back() == PERCENT || str.back() == RPAREN)
                isAddPercent = true;

            else if (str.size() >= 2 && !isSymbol(str[str.size() - 2]))
            {
                CorrectChop();
                isAddPercent = true;
            }
        }

        if (isAddPercent)
            str.push_back(PERCENT);
    }

    emit strUpdated(str);
}

void Backend::addBracket(bool isOpen)
{
    ifHavePrevError();

    if (!str.isEmpty() && str.back() == DOT)
        str.chop(1);

    if (isOpen) // '(' - LPAREN
    {
        ++lr_brackets;
        str.push_back(LPAREN);
    }
    else if (lr_brackets > 0 && str.back() != LPAREN) // ')' - RPAREN
    {
        --lr_brackets;
        str.push_back(RPAREN);
    }

    emit strUpdated(str);
}

void Backend::getResult()
{
    if (lr_brackets == 0)
    {
        while (!str.isEmpty() && str.back() != RPAREN && str.back() != PERCENT && isSymbol(str.back()))
            CorrectChop();

        if (!str.isEmpty())
        {
            QString last_str = str;
            try
            {
                Lexer lexer;
                lexer.tokenize(str);
                Parser parser(lexer.getLexema());
                Evaluator eval(parser.getTree());
                str = eval.getResult();
                if (str != last_str)
                {
                    emit histUpdated(last_str);
                    history.push_back(last_str + QChar('=') + str);
                    emit getHistoryList();
                }
            }
            catch (const std::runtime_error& error)
            {
                str = error.what();
            }
        }
        emit strUpdated(str);
    }
    else
    {
        remove(REMOVE_ALL);
        str = "the bracket is not closed";
    }
}

QStringList Backend::getHistoryList()
{
    return history;
}

bool Backend::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        const int key = keyEvent->key();
        const QString textStr = keyEvent->text();

        if (!textStr.isEmpty() && QRegularExpression("[0-9]").match(textStr.back()).hasMatch())
            addDigit(textStr.back());
        else if (!textStr.isEmpty() && textStr.back() == QChar('='))
            getResult();
        else
        {
            switch (key)
            {
            case Qt::Key_Minus:      addOper(MINUS);      break;
            case Qt::Key_Asterisk:   addOper(MULTIPLY);   break;
            case Qt::Key_Slash:      addOper(DIVIDE);     break;
            case Qt::Key_Plus:       addOper(PLUS);       break;
            case Qt::Key_Period:     addPoint();          break;
            case Qt::Key_Percent:    addPercent();        break;
            case Qt::Key_ParenLeft:  addBracket(true);    break;
            case Qt::Key_ParenRight: addBracket(false);   break;
            case Qt::Key_Enter:
            case Qt::Key_Return:     getResult();         break;
            case Qt::Key_Backspace:
                if (keyEvent->modifiers() & Qt::ControlModifier)
                    remove(REMOVE_STR);
                else
                    remove(REMOVE_ELEM);

                break;
            }
        }

        return true;
    }

    return false;
}

void Backend::ChangeSignASign(int index)
{
    QChar &elem = str[index];
    if (elem == MINUS)
    {
        if ((index >= 1 && NneedSignClarif.indexOf(str[index - 1]) != -1) || index < 1)
            str.remove(index, 1);

        else
            elem = PLUS;
    }
    else if (elem == PLUS)
        elem = MINUS;

    else
        str.insert(index + 1, MINUS);
}

void Backend::CorrectChop()
{
    QChar lastElem = str.back();

    if      (lastElem == LPAREN) lr_brackets--;
    else if (lastElem == RPAREN) lr_brackets++;

    str.chop(1);
}

void Backend::ifHavePrevError()
{
    if (!str.isEmpty() && str.back().isLetter())
        str.clear();
}
