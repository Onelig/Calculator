#include "evaluator.h"
#include <gtest/gtest.h>

class EvaluatorTest : public ::testing::Test
{
protected:
    Evaluator evaluator_;
};

using boost::multiprecision::cpp_dec_float_100;

TEST_F(EvaluatorTest, EvalSimpleExpression)
{
    QString expected_result("489");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_PLUS, 
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("120")),
        std::make_shared<Node>(
            TOKEN_MUL,
            std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("123")),
            std::make_shared<Node>(
                TOKEN_ROOT,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("9"))
            )    
        )
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}


TEST_F(EvaluatorTest, EvalBasicExpression)
{
    QString expected_result("502.00319");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_MINUS,
        std::make_shared<Node>(
            TOKEN_PLUS,
            std::make_shared<Node>(
                TOKEN_MINUS,
                std::make_shared<Node>(
                    TOKEN_ROOT,
                    std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("81"))
                )
            ),
            std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("613"))
        ),
        std::make_shared<Node>(
            TOKEN_MUL,
            std::make_shared<Node>(
                TOKEN_DIV,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("51")),
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("32.001"))
            ),
            std::make_shared<Node>(
                TOKEN_ROOT,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("4096"))
            )      
        )
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}


TEST_F(EvaluatorTest, EvalEmptyExpression)
{
    evaluator_.setRoot(nullptr);
    ASSERT_NO_THROW(evaluator_.getResult());
}


TEST_F(EvaluatorTest, EvalThrowErrorValSkippedExpression)
{
    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_PLUS, 
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("120")),
        std::make_shared<Node>(
            TOKEN_MUL,
            std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("123"))
        )
    );

    evaluator_.setRoot(tree);
    ASSERT_THROW(evaluator_.getResult(), std::runtime_error);
}


TEST_F(EvaluatorTest, EvalThrowErrorUndValueExpression)
{
    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_LPAREN,
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("120"))
    );

    evaluator_.setRoot(tree);
    ASSERT_THROW(evaluator_.getResult(), std::runtime_error);
}


TEST_F(EvaluatorTest, EvalOneArgExpression)
{
    QString expected_result("123.312");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        std::make_shared<const cpp_dec_float_100>("123.3120")
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}


TEST_F(EvaluatorTest, EvalDivisionByZero) 
{
    QString expected_result("inf");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_DIV,
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("42")),
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("0"))
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}


TEST_F(EvaluatorTest, EvalNegativeRoot) 
{
    QString expected_result("nan");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_ROOT,
        std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("-9"))
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}

TEST_F(EvaluatorTest, EvalComplexExpression)
{
    QString expected_result("5058.56789");

    std::shared_ptr<Node> tree = std::make_shared<Node>(
        TOKEN_PLUS,
        std::make_shared<Node>(
            TOKEN_MUL,
            std::make_shared<Node>(
                TOKEN_ROOT,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("256"))  
            ),
            std::make_shared<Node>(
                TOKEN_DIV,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("1024")),
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("4"))   
            )
        ),
        std::make_shared<Node>(
            TOKEN_MINUS,
            std::make_shared<Node>(
                TOKEN_PLUS,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("1000")),
                std::make_shared<Node>(
                    TOKEN_ROOT,
                    std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("81")) 
                )
            ),
            std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("46.43211"))
        )
    );

    evaluator_.setRoot(tree);

    QString result;
    ASSERT_NO_THROW(result = evaluator_.getResult());

    ASSERT_EQ(result, expected_result);
}