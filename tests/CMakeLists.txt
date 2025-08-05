find_package(GTest REQUIRED)


set(LexerPass lexer_pass.cpp)
add_executable(lexer_test ${LexerPass})
target_link_libraries(lexer_test PRIVATE GTest::gtest_main lexer)

add_test(Lexer lexer_test)


set(ParserPass parser_pass.cpp) 
add_executable(parser_test ${ParserPass})
target_link_libraries(parser_test PRIVATE GTest::gtest_main parser)

add_test(Parser parser_test)


set(EvaluatorPass evaluator_pass.cpp)
add_executable(evaluator_test ${EvaluatorPass})
target_link_libraries(evaluator_test PRIVATE GTest::gtest_main evaluator)

add_test(Evaluator evaluator_test)