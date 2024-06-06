cmake_minimum_required(VERSION 3.5)

project(Qwicky VERSION 0.1 LANGUAGES CXX)

# Qt settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Core UiTools)

# subdirectory
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeLists.txt)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


qt_add_executable(Qwicky
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    data/mainresources.qrc
)

target_link_libraries(Qwicky
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::UiTools
)

target_link_libraries(Qwicky PRIVATE Qt6::Sql)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qwicky)
endif()

