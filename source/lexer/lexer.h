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

struct Token
{
    const TokenType type;
    const QString value;
};

class Lexer
{
private:
    std::list<Token> tokens;

public:
    explicit Lexer(const QString& expr);
};
