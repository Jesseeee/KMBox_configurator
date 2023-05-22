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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Network Gui Widgets)

set(PROJECT_SOURCES
    source/main.cpp
	source/TabWindow.cpp
	source/TabWindow.hpp
	source/LayoutManager.cpp
	source/LayoutManager.hpp
	source/configuration/ConfigurationWindow.cpp
	source/configuration/ConfigurationWindow.hpp
	source/configuration/ConfigurationManager.cpp
	source/configuration/ConfigurationManager.hpp
	source/topology/TopologyWindow.cpp
    source/topology/TopologyWindow.hpp
	source/topology/Arrow.cpp
	source/topology/Arrow.hpp
	source/topology/ItemDetailWidget.cpp
	source/topology/ItemDetailWidget.hpp
	source/topology/TopologyItem.cpp
	source/topology/TopologyItem.hpp
	source/topology/TopologyScene.cpp
	source/topology/TopologyScene.hpp
	source/layout/LayoutWindow.cpp
	source/layout/LayoutWindow.hpp
	source/layout/RectDetailWidget.cpp
	source/layout/RectDetailWidget.hpp
	source/layout/LayoutScene.cpp
	source/layout/LayoutScene.hpp
	source/layout/ResizeableRectItem.cpp
	source/layout/ResizeableRectItem.hpp
	source/network/KMAPIHandler.cpp
	source/network/KMAPIHandler.hpp
)

qt_add_executable(KMBox_configurator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(KMBox_configurator PRIVATE
    Qt6::Core
	Qt6::Network
	Qt6::Gui
    Qt6::Widgets
)

target_include_directories(KMBox_configurator PRIVATE ./source/)

target_include_directories(KMBox_configurator PRIVATE
	"C:\\Qt\\Tools\\mingw1120_64\\lib\\gcc\\x86_64-w64-mingw32\\11.2.0\\include\\c++\\bits"
)

qt_add_resources(KMBox_configurator "configurator"
    PREFIX
        "/"
    FILES
		"images/bringtofront.png"
		"images/okay.png"
		"images/delete.png"
		"images/save.png"
		"images/linepointer.png"
		"images/pointer.png"
		"images/sendtoback.png"
		"images/server.png"
		"images/display.png"
		"images/KMBox.png"
)

install(TARGETS KMBox_configurator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(KMBox_configurator)