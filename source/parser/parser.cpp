#include "parser.h"

Node::Node(std::shared_ptr<const boost::multiprecision::cpp_dec_float_100> value, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : value(std::move(value)), oper(TOKEN_NUMBER), right(std::move(right)), left(std::move(left))
{ }

Node::Node(TokenType oper, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : oper(oper), right(std::move(right)), left(std::move(left))
{ }

boost::multiprecision::cpp_dec_float_100 Node::getValue()
{
    return *value;
}

const Token& Parser::peek()
{
    return *iter;
}

const Token& Parser::get()
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
    {
        auto type = get().type;
        return std::make_shared<Node>(type, UOper());
    }
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
    std::shared_ptr<Node> result = UOper();

    while (peek().type == TOKEN_MUL || peek().type == TOKEN_DIV)
    {
        auto type = get().type;
        result = std::make_shared<Node>(type, result, UOper());
    }
    return result;
}

std::shared_ptr<Node> Parser::minPriorityBOper() // '+', '-'
{
    std::shared_ptr<Node> result = maxPriorityBOper();

    while (peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS)
    {
        auto type = get().type;
        result = std::make_shared<Node>(type, result, maxPriorityBOper());
    }
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
