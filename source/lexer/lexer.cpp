#include "lexer.h"
#include "symbols.h"
#include <QRegularExpression>

Lexer::Lexer(const QString &expr)
{
    QString::const_iterator citer = expr.cbegin();
    bool isOperMSkipped = false;
    while (citer != expr.cend())
    {
        if (citer->isDigit())
        {
            if (isOperMSkipped)
                tokens.push_back(Token{TOKEN_MUL});

            isOperMSkipped = true;

            QString::const_iterator itnum_end = std::find_if(citer + 1, expr.cend(), [](QChar element){ return element != DOT && isSymbol(element); });
            tokens.push_back(Token{TOKEN_NUMBER, std::make_shared<boost::multiprecision::cpp_dec_float_100>(expr.mid(std::distance(expr.cbegin(), citer), std::distance(citer, itnum_end)).toStdString())});
            citer = itnum_end;
        }
        else if (*citer == PLUS)
        {
            isOperMSkipped = false;
            tokens.push_back(Token{TOKEN_PLUS});
            ++citer;
        }
        else if (*citer == MINUS)
        {
            isOperMSkipped = false;
            tokens.push_back(Token{TOKEN_MINUS});
            ++citer;
        }
        else if (*citer == LPAREN)
        {
            if (isOperMSkipped)
            {
                tokens.push_back(Token{TOKEN_MUL});
                isOperMSkipped = false;
            }
            tokens.push_back(Token{TOKEN_LPAREN});
            ++citer;
        }
        else if (*citer == RPAREN)
        {
            isOperMSkipped = true;
            tokens.push_back(Token{TOKEN_RPAREN});
            ++citer;
        }
        else if (*citer == MULTIPLY)
        {
            isOperMSkipped = false;
            tokens.push_back(Token{TOKEN_MUL});
            ++citer;
        }
        else if (*citer == DIVIDE)
        {
            isOperMSkipped = false;
            tokens.push_back(Token{TOKEN_DIV});
            ++citer;
        }
        else if (*citer == ROOT)
        {
            if (isOperMSkipped)
            {
                tokens.push_back(Token{TOKEN_MUL});
                isOperMSkipped = false;
            }
            tokens.push_back(Token{TOKEN_ROOT});
            ++citer;
        }
        else if (*citer == PERCENT)
        {
            isOperMSkipped = true;
            tokens.push_back(Token{TOKEN_DIV});
            tokens.push_back(Token{TOKEN_NUMBER, std::make_shared<boost::multiprecision::cpp_dec_float_100>("100")});
            ++citer;
        }
    }

    tokens.push_back(Token{TOKEN_END});
}

const std::list<Token> &Lexer::getLexema()
{
    return tokens;
}
