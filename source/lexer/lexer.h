#pragma once
#include <QString>
#include <list>

enum TokenType
{
    TOKEN_LPAREN, // '('
    TOKEN_RPAREN, // ')'
    TOKEN_NUMBER, // [0 - 9]
    TOKEN_PLUS,   // '+'
    TOKEN_MINUS,  // '-'
    TOKEN_MUL,    // '*'
    TOKEN_DIV,    // '/'
    TOKEN_ROOT,   // '√'
    TOKEN_PRECENT // '%'
};

struct Token final
{
    const TokenType type;
    const double value;
};

class Lexer final
{
private:
    std::list<Token> tokens;

public:
    explicit Lexer(const QString& expr);
    const std::list<Token>& getLexema();
};
