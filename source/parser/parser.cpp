#include "parser.h"

Node::Node(std::shared_ptr<const boost::multiprecision::cpp_dec_float_100> value)
    : value(std::move(value)), oper(TOKEN_NUMBER), right(nullptr), left(nullptr)
{ }

Node::Node(TokenType oper, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : oper(oper), right(std::move(right)), left(std::move(left))
{ }

boost::multiprecision::cpp_dec_float_100 Node::getValue()
{
    if (value != nullptr)
        return *value;
    else 
        throw std::runtime_error("Invalid number");   
}

const Token& Parser::peek()
{
    if (iter == end)
        throw std::runtime_error("Parser error: the sequence of characters is broken.");

    return *iter;
}

const Token& Parser::get()
{
    return *(iter++);
}

std::shared_ptr<Node> Parser::getNum()
{
    if (peek().type != TOKEN_NUMBER)
        throw std::runtime_error("Parser error: the sequence of characters is broken.");

    return std::make_shared<Node>(get().value);
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
        if (peek().type == TOKEN_RPAREN)
            get(); // skip RPAREN
        else 
            throw std::runtime_error("Parser error: Right paren was skipped.");
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
{
    parse(lexema);
}

void Parser::parse(const std::list<Token> &lexema)
{
    if (lexema.size() > 0 && lexema.begin()->type != TOKEN_END)
    {
        iter = lexema.begin();
        end = lexema.end();
        root = minPriorityBOper();
        if (peek().type != TOKEN_END)
            throw std::runtime_error("Parser error: the sequence of characters is broken.");
    }
}

std::shared_ptr<Node> Parser::getTree()
{
    return std::move(root);
}
