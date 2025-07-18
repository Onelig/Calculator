#pragma once
#include "lexer.h"
#include <list>
#include <memory>

class Node final
{
private:
    double value;
    TokenType oper;

public:
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> left;

public:
    Node(double value, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);
    Node(TokenType oper, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr);

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
};
