#include "lexer.h"
#include <gtest/gtest.h>

class LexerTest : public ::testing::Test
{
protected:
    Lexer lexer_;
};

using boost::multiprecision::cpp_dec_float_100;

TEST_F(LexerTest, TokenizeSimpleInput) 
{
    std::list<Token> expected_tokens
    {
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("9381")},
        Token{TOKEN_MUL},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("351.215")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(lexer_.tokenize(MINUS + QString("9381") + MULTIPLY + "351" + DOT + "215"));

    const std::list<Token>& tokens = lexer_.getLexema();
    ASSERT_EQ(tokens.size(), expected_tokens.size());

    for (std::list<Token>::const_iterator iter1 = tokens.cbegin(), iter2 = expected_tokens.cbegin(); iter1 != tokens.cend(); ++iter1, ++iter2)
    {
        const auto& [tokentype, value]{ *iter1 };
        const auto& [expected_tokentype, expected_value]{ *iter2 };

        ASSERT_EQ(tokentype, expected_tokentype);

        if (tokentype == TOKEN_NUMBER)
            ASSERT_EQ(*value, *expected_value);
        else 
            ASSERT_EQ(value, expected_value); // value == nullptr && expected_value == nullptr
    }    
}
 

TEST_F(LexerTest, TokenizeBasicExpression) 
{
    std::list<Token> expected_tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_ROOT},
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("999")},
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("52")},
        Token{TOKEN_MUL},
        Token{TOKEN_LPAREN},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("84")},
        Token{TOKEN_RPAREN},
        Token{TOKEN_MUL},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("71")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(lexer_.tokenize(QString(ROOT) + ROOT + ROOT + "999" + MINUS + "52" + LPAREN + "84" + RPAREN + "71"));

    const std::list<Token>& tokens = lexer_.getLexema();
    ASSERT_EQ(tokens.size(), expected_tokens.size());

    for (std::list<Token>::const_iterator iter1 = tokens.cbegin(), iter2 = expected_tokens.cbegin(); iter1 != tokens.cend(); ++iter1, ++iter2)
    {
        const auto& [tokentype, value]{ *iter1 };
        const auto& [expected_tokentype, expected_value]{ *iter2 };

        ASSERT_EQ(tokentype, expected_tokentype);

        if (tokentype == TOKEN_NUMBER && expected_tokentype == TOKEN_NUMBER)
            ASSERT_EQ(*value, *expected_value);
        else 
            ASSERT_EQ(value, expected_value); // value == nullptr && expected_value == nullptr
    }    
}


TEST_F(LexerTest, TokenizeIntermediateExpression) 
{
    std::list<Token> expected_tokens
    {
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("81")},
        Token{TOKEN_PLUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("91")},
        Token{TOKEN_MUL},
        Token{TOKEN_ROOT},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("1")},
        Token{TOKEN_DIV},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("100")},
        Token{TOKEN_DIV},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("10")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(lexer_.tokenize(ROOT + QString("81") + PLUS + "91" + ROOT + "1" + PERCENT + DIVIDE + "10"));

    const std::list<Token>& tokens = lexer_.getLexema();
    ASSERT_EQ(tokens.size(), expected_tokens.size());

    for (std::list<Token>::const_iterator iter1 = tokens.cbegin(), iter2 = expected_tokens.cbegin(); iter1 != tokens.cend(); ++iter1, ++iter2)
    {
        const auto& [tokentype, value]{ *iter1 };
        const auto& [expected_tokentype, expected_value]{ *iter2 };

        ASSERT_EQ(tokentype, expected_tokentype);

        if (tokentype == TOKEN_NUMBER)
            ASSERT_EQ(*value, *expected_value);
        else 
            ASSERT_EQ(value, expected_value); // value == nullptr && expected_value == nullptr
    }    
}


TEST_F(LexerTest, TokenizeEmptyExpression) 
{
    std::list<Token> expected_tokens
    {
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(lexer_.tokenize(""));

    const std::list<Token>& tokens = lexer_.getLexema();
    ASSERT_EQ(tokens.size(), expected_tokens.size());

    for (std::list<Token>::const_iterator iter1 = tokens.cbegin(), iter2 = expected_tokens.cbegin(); iter1 != tokens.cend(); ++iter1, ++iter2)
    {
        const auto& [tokentype, value]{ *iter1 };
        const auto& [expected_tokentype, expected_value]{ *iter2 };

        ASSERT_EQ(tokentype, expected_tokentype);

        if (tokentype == TOKEN_NUMBER)
            ASSERT_EQ(*value, *expected_value);
        else 
            ASSERT_EQ(value, expected_value); // value == nullptr && expected_value == nullptr
    }    
}


TEST_F(LexerTest, TokenizeOneNumExpression) 
{
    std::list<Token> expected_tokens
    {
        Token{TOKEN_MINUS},
        Token{TOKEN_NUMBER, std::make_shared<const cpp_dec_float_100>("31")},
        Token{TOKEN_END}
    };

    ASSERT_NO_THROW(lexer_.tokenize("-31"));

    const std::list<Token>& tokens = lexer_.getLexema();
    ASSERT_EQ(tokens.size(), expected_tokens.size());

    for (std::list<Token>::const_iterator iter1 = tokens.cbegin(), iter2 = expected_tokens.cbegin(); iter1 != tokens.cend(); ++iter1, ++iter2)
    {
        const auto& [tokentype, value]{ *iter1 };
        const auto& [expected_tokentype, expected_value]{ *iter2 };

        ASSERT_EQ(tokentype, expected_tokentype);

        if (tokentype == TOKEN_NUMBER)
            ASSERT_EQ(*value, *expected_value);
        else 
            ASSERT_EQ(value, expected_value); // value == nullptr && expected_value == nullptr
    }    
}


TEST_F(LexerTest, TokenizeThrowErrorExpression) 
{
    ASSERT_THROW(lexer_.tokenize("981`23"), std::runtime_error);
    ASSERT_THROW(lexer_.tokenize("d2921"), std::runtime_error);
}