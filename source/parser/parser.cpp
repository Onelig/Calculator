#include "parser.h"

Parser::Parser(const std::list<TokenType> &lexema)
{

}

Node::Node(double value, std::unique_ptr<Node> right, std::unique_ptr<Node> left)
    : value(value), oper(TOKEN_NUMBER), right(std::move(right)), left(std::move(left))
{ }

Node::Node(TokenType oper, std::unique_ptr<Node> right, std::unique_ptr<Node> left)
    : oper(oper), right(std::move(right)), left(std::move(left))
{ }


