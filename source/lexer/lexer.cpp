#include "lexer.h"
#include "symbols.h"
#include <QRegularExpression>

Lexer::Lexer(const QString &expr)
{
    QString::const_iterator citer = expr.cbegin();
    while (citer != expr.cend())
    {
        if (citer->isDigit())
        {
            QString::const_iterator itnum_end = std::find_if(citer + 1, expr.cend(), [](QChar element){ return element != DOT && isSymbol(element); });
            tokens.push_back(Token{TOKEN_NUMBER, expr.mid(std::distance(expr.cbegin(), citer), std::distance(citer, itnum_end))});
            citer = itnum_end;
        }
        else if (*citer == PLUS)
        {
            tokens.push_back(Token{TOKEN_PLUS});
            ++citer;
        }
        else if (*citer == MINUS)
        {
            tokens.push_back(Token{TOKEN_MINUS});
            ++citer;
        }
        else if (*citer == LPAREN)
        {
            tokens.push_back(Token{TOKEN_LPAREN});
            ++citer;
        }
        else if (*citer == RPAREN)
        {
            tokens.push_back(Token{TOKEN_RPAREN});
            ++citer;
        }
        else if (*citer == MULTIPLY)
        {
            tokens.push_back(Token{TOKEN_MUL});
            ++citer;
        }
        else if (*citer == DIVIDE)
        {
            tokens.push_back(Token{TOKEN_DIV});
            ++citer;
        }
        else if (*citer == ROOT) // '√'
        {
            tokens.push_back(Token{TOKEN_ROOT});
            ++citer;
        }
        else if (*citer == PERCENT)
        {
            tokens.push_back(Token{TOKEN_PRECENT});
            ++citer;
        }
    }
}
