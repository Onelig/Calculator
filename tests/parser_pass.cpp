#include "parser.h"
#include <gtest/gtest.h>

class ParserTest : public ::testing::Test
{
protected:
    Parser parser_;
};

using boost::multiprecision::cpp_dec_float_100;

void isEqualNode(const std::shared_ptr<Node> tree1, const std::shared_ptr<Node> tree2)
{
    if (tree1 && tree2)
    {
        ASSERT_EQ(tree1->oper, tree2->oper);
        if (tree1->oper == TOKEN_NUMBER)
            ASSERT_EQ(tree1->getValue(), tree2->getValue());

        isEqualNode(tree1->left, tree2->left);
        isEqualNode(tree1->right, tree2->right);
    }
    else
        ASSERT_EQ(tree1, tree2); // tree1 == nullptr && tree2 == nullptr
}


TEST_F(ParserTest, SimpleExpression)
{
    std::shared_ptr<Node> expected_tree = std::make_shared<Node>(
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

    std::list<Token> tokens
    {
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("120")},
        Token{TOKEN_PLUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("123")},
        Token{TOKEN_MUL},
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("9")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(parser_.parse(tokens));

    std::shared_ptr<Node> tree = parser_.getTree();

    isEqualNode(tree, expected_tree);
}


TEST_F(ParserTest, BasicExpression)
{
    std::shared_ptr<Node> expected_tree = std::make_shared<Node>(
        TOKEN_DIV, 
        std::make_shared<Node>(
            TOKEN_ROOT,
            std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("99981.1"))
            ),
        std::make_shared<Node>(
            TOKEN_ROOT,
            std::make_shared<Node>(
                TOKEN_MINUS,
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("891")),
                std::make_shared<Node>(
                    TOKEN_MUL,
                    std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("914")),
                    std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("0"))
                )
            )
        )
    );

    std::list<Token> tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("99981.1")},
        Token{TOKEN_DIV},
        Token{TOKEN_ROOT},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("891")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("914")},
        Token{TOKEN_MUL},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("0")},
        Token{TOKEN_RPAREN},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(parser_.parse(tokens));

    std::shared_ptr<Node> tree = parser_.getTree();

    isEqualNode(tree, expected_tree);
}


TEST_F(ParserTest, IntermediateExpression)
{
    std::shared_ptr<Node> expected_tree = std::make_shared<Node>(
        TOKEN_MINUS,
        std::make_shared<Node>(
            TOKEN_PLUS,
            std::make_shared<Node>(
                TOKEN_MINUS,
                std::make_shared<Node>(
                    TOKEN_ROOT,
                    std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("81.31"))
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
                std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("4161"))
            )      
        )
    );

    std::list<Token> tokens
    {
        Token{TOKEN_MINUS},
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("81.31")},
        Token{TOKEN_PLUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("613")},
        Token{TOKEN_MINUS},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("51")},
        Token{TOKEN_DIV},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("32.001")},
        Token{TOKEN_MUL},
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("4161")},
        Token{TOKEN_RPAREN},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(parser_.parse(tokens));

    std::shared_ptr<Node> tree = parser_.getTree();

    isEqualNode(tree, expected_tree);
}


TEST_F(ParserTest, EmptyExpression)
{
    std::shared_ptr<Node> expected_tree = std::make_shared<Node>(std::make_shared<const cpp_dec_float_100>("120"));

    std::list<Token> tokens
    {
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("120")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(parser_.parse(tokens));

    std::shared_ptr<Node> tree = parser_.getTree();

    isEqualNode(tree, expected_tree);
}


TEST_F(ParserTest, OneNumExpression)
{
    std::shared_ptr<Node> expected_tree;

    std::list<Token> tokens
    {
        
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(parser_.parse(tokens));

    std::shared_ptr<Node> tree = parser_.getTree();

    isEqualNode(tree, expected_tree);
}


TEST_F(ParserTest, ThrowErrorExpressionDoubleOper)
{
    std::list<Token> tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("99981.1")},
        Token{TOKEN_DIV},
        Token{TOKEN_ROOT},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("891")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("914")},
        Token{TOKEN_MUL},
        Token{TOKEN_MUL}, // ! 
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("0")},
        Token{TOKEN_RPAREN},
        Token{TOKEN_END}
    };

    ASSERT_THROW(parser_.parse(tokens), std::runtime_error);
}


TEST_F(ParserTest, ThrowErrorExpressionNoEnd)
{
    std::list<Token> tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("99981.1")},
        Token{TOKEN_DIV},
        Token{TOKEN_ROOT},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("891")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("914")},
        Token{TOKEN_MUL},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("0")},
        Token{TOKEN_RPAREN}
        // Token{TOKEN_END}
    };

    ASSERT_THROW(parser_.parse(tokens), std::runtime_error);
}


TEST_F(ParserTest, ThrowErrorExpressionSkipParen)
{
    std::list<Token> tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("99981.1")},
        Token{TOKEN_DIV},
        Token{TOKEN_ROOT},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("891")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("914")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("0")},
        // Token{TOKEN_RPAREN}
        Token{TOKEN_END}
    };

    ASSERT_THROW(parser_.parse(tokens), std::runtime_error);
}