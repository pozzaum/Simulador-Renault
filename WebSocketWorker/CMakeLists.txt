cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(Qt6_DIR "C:/Qt/6.7.3/msvc2019_64/lib/cmake/Qt6")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

add_library(WebSocketWorker websocketworker.cpp websocketworker.h)

target_link_libraries(WebSocketWorker Qt6::Core Qt6::WebSockets)

target_include_directories(WebSocketWorker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
