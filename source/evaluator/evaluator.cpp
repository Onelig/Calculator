#include "evaluator.h"

boost::multiprecision::cpp_dec_float_100 Evaluator::getResult_(std::shared_ptr<Node> root_)
{
    switch (root_->oper)
    {
    case TOKEN_NUMBER:
        return root_->getValue();

    case TOKEN_ROOT:
        return sqrt(getResult_(root_->left));

    case TOKEN_MINUS:
        if (root_->right)
            return getResult_(root_->left) - getResult_(root_->right);
        else
            return -getResult_(root_->left);

    case TOKEN_PLUS:
        return getResult_(root_->left) + getResult_(root_->right);

    case TOKEN_MUL:
        return getResult_(root_->left) * getResult_(root_->right);

    case TOKEN_DIV:
        return getResult_(root_->left) / getResult_(root_->right);

    default:
        throw std::runtime_error("Evaluator error: Uncertain token.");
        break;
    }
}

Evaluator::Evaluator(std::shared_ptr<Node> root)
    : root(std::move(root))
{ }

bool Evaluator::hasError()
{
    return !error_message.isEmpty();
}

const QString& Evaluator::what() const
{
    return error_message;
}

QString Evaluator::getResult()
{
    std::string str = getResult_(root).str(5, std::ios_base::fixed);

    while (!str.empty() && str.back() == '0')
        str.pop_back();

    if (!str.empty() && str.back() == '.')
        str.pop_back();

    return QString::fromStdString(str);
}
