#include "parser.h"

Node::Node(double value, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : value(value), oper(TOKEN_NUMBER), right(std::move(right)), left(std::move(left))
{ }

Node::Node(TokenType oper, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : oper(oper), right(std::move(right)), left(std::move(left))
{ }

double Node::getValue()
{
    return value;
}

Token Parser::peek()
{
    return *iter;
}

Token Parser::get()
{
    return *(iter++);
}

std::shared_ptr<Node> Parser::getNum()
{
    return (peek().type == TOKEN_NUMBER ? std::make_shared<Node>(get().value) : nullptr);
}

std::shared_ptr<Node> Parser::UOper() // '√', '(', ')', U'-'
{
    if (peek().type == TOKEN_ROOT || peek().type == TOKEN_MINUS)
        return std::make_shared<Node>(get().type, UOper());

    else if (peek().type == TOKEN_LPAREN)
    {
        get();
        std::shared_ptr<Node> mroot = minPriorityBOper();
        get(); // skip RPAREN
        return mroot;
    }

    return getNum();
}

std::shared_ptr<Node> Parser::maxPriorityBOper() // '*', '/'
{
    std::shared_ptr<Node> loperand = UOper(),
                          result   = nullptr;

    while (peek().type == TOKEN_MUL || peek().type == TOKEN_DIV)
        result = std::make_shared<Node>(get().type, (result ? result : loperand), UOper());

    return result;
}

std::shared_ptr<Node> Parser::minPriorityBOper() // '+', '-'
{
    std::shared_ptr<Node> loperand = maxPriorityBOper(),
                          result   = nullptr;

    while (peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS)
        result = std::make_shared<Node>(get().type, (result ? result : loperand), maxPriorityBOper());

    return result;
}

Parser::Parser(const std::list<Token> &lexema)
    : iter(lexema.cbegin())
{
    root = minPriorityBOper();
}

std::shared_ptr<Node> Parser::getTree()
{
    return std::move(root);
}
