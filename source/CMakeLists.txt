qt6_add_resources(QML_RESOURCES "${CMAKE_SOURCE_DIR}/resources/qml/qml.qrc")

qt_add_executable(appCalculator
    main.cpp
    ${QML_RESOURCES}
    backend/backend.cpp
    lexer/lexer.cpp
    parser/parser.cpp

    symbols/symbols.h
    lexer/lexer.h
    backend/backend.h
    parser/parser.h
)

target_include_directories(appCalculator PRIVATE symbols backend lexer parser)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCalculator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCalculator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCalculator PRIVATE Qt6::Core Qt6::Quick Qt6::Qml)

include(GNUInstallDirs)
install(TARGETS appCalculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
