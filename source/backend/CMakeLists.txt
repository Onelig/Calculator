add_library( backend 
    backend.cpp
)

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(backend PUBLIC evaluator Qt6::Quick Qt6::Qml)