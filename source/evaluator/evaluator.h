#pragma once
#include "parser.h"

class Evaluator
{
private:
    std::shared_ptr<Node> root;
    double getResult_(std::shared_ptr<Node> root_);

public:
    explicit Evaluator(std::shared_ptr<Node> root);
    double getResult();
};
