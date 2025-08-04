add_library( evaluator 
    evaluator.cpp
)

target_include_directories(evaluator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(evaluator PUBLIC parser)