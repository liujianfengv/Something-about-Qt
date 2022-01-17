cmake_minimum_required(VERSION 3.14)

project(ImageLoader LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ./*.cpp ./*.h)
add_executable(ImageLoader
  main.cpp
  ${SOURCE_FILES}
)
target_link_libraries(ImageLoader Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
