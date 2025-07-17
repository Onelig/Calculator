#pragma once
#include "lexer.h"
#include <list>

class Node final
{
private:
    double value;
    TokenType oper;

    std::unique_ptr<Node> right;
    std::unique_ptr<Node> left;

public:
    Node(double value, std::unique_ptr<Node> right = nullptr, std::unique_ptr<Node> left = nullptr);
    Node(TokenType oper, std::unique_ptr<Node> right = nullptr, std::unique_ptr<Node> left = nullptr);
};

class Parser final
{
private:
    std::unique_ptr<Node> tree;

public:
    explicit Parser(const std::list<TokenType>& lexema);
};
