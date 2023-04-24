cmake_minimum_required(VERSION 3.5)

project(
	KMBox_configurator
	VERSION 0.1
	DESCRIPTION "KMBox configurator GUI application"
	LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_SOURCES
    source/main.cpp
	source/MainWindow.cpp
    source/MainWindow.hpp
	source/Arrow.cpp
	source/Arrow.hpp
	source/DiagramItem.cpp
	source/DiagramItem.hpp
	source/DiagramScene.cpp
	source/DiagramScene.hpp
)

qt_add_executable(KMBox_configurator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(KMBox_configurator PRIVATE
    Qt6::Core
	Qt6::Gui
    Qt6::Widgets
)

qt_add_resources(KMBox_configurator "configurator"
    PREFIX
        "/"
    FILES
		"images/background1.png"
		"images/background2.png"
		"images/background3.png"
		"images/background4.png"
		"images/bold.png"
		"images/bringtofront.png"
		"images/delete.png"
		"images/floodfill.png"
		"images/italic.png"
		"images/linecolor.png"
		"images/linepointer.png"
		"images/pointer.png"
		"images/sendtoback.png"
		"images/textpointer.png"
		"images/underline.png"
)

install(TARGETS KMBox_configurator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(KMBox_configurator)