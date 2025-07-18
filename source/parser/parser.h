#pragma once
#include "lexer.h"
#include <memory>

class Node final
{
private:
    double value;

public:
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> left;

    const TokenType oper;
public:
    Node(double value,   std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);
    Node(TokenType oper, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);
    double getValue(); // when oper == TOKEN_NUMBER
};

class Parser final
{
private: // fields
    std::shared_ptr<Node> root;

private: // useful instruments
    std::list<Token>::const_iterator iter;
    Token peek();
    Token get();

private: // main methods
    std::shared_ptr<Node> getNum();
    std::shared_ptr<Node> UOper();            // '√', '(', ')', U'-'
    std::shared_ptr<Node> maxPriorityBOper(); // '*', '/'
    std::shared_ptr<Node> minPriorityBOper(); // '+', '-'

public:
    explicit Parser(const std::list<Token>& lexema);
    std::shared_ptr<Node> getTree();
};
