add_library(lexer
    lexer.cpp
)

target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

target_link_libraries(lexer
    PUBLIC Qt6::Core symbols Boost::headers)
