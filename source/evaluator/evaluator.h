#pragma once
#include "parser.h"

class Evaluator
{
private:
    std::shared_ptr<Node> root;
    boost::multiprecision::cpp_dec_float_100 getResult_(std::shared_ptr<Node> root_);
    QString error_message;

public:
    explicit Evaluator(std::shared_ptr<Node> root);
    QString getResult();
    bool hasError();
    const QString& what() const;
};
