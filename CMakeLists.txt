cmake_minimum_required(VERSION 3.5)

project(KMBox_configurator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

qt_add_executable(KMBox_configurator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(KMBox_configurator PRIVATE
    Qt6::Core
    Qt6::Widgets
)

qt_add_resources(KMBox_configurator "configurator"
    PREFIX
        "/icons"
    FILES
        "icons/server.png"
)

install(TARGETS KMBox_configurator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(KMBox_configurator)
