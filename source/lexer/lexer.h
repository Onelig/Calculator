#pragma once

#include <QString>
#include <list>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "symbols.h"

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
    TOKEN_END     // end of operators
};

struct Token final
{
    const TokenType type;
    const std::shared_ptr<const boost::multiprecision::cpp_dec_float_100> value;    
};

class Lexer final
{
private:
    std::list<Token> tokens;

public:
    explicit Lexer() = default;
    explicit Lexer(const QString& expr);
    void tokenize(const QString& expr);
    const std::list<Token>& getLexema();
};
