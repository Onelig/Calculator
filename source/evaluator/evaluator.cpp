#include "evaluator.h"
#include <math.h>

double Evaluator::getResult_(std::shared_ptr<Node> root_)
{
    switch (root_->oper)
    {
    case TOKEN_NUMBER:
        return root_->getValue();

    case TOKEN_ROOT:
        return std::sqrt(getResult_(root_->left));

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
    {
        return getResult_(root_->left) / getResult_(root_->right);
    }
    }
}


Evaluator::Evaluator(std::shared_ptr<Node> root)
    : root(std::move(root))
{ }

double Evaluator::getResult()
{
    return getResult_(root);
}
