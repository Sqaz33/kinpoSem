cmake_minimum_required(VERSION 3.10)

project(BRN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=================================
# Необходимо добавить qt5 в PATH
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
#=================================

find_package(Qt5 COMPONENTS REQUIRED Core Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(BRN)

target_include_directories(
        BRN PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB srcs 
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
target_sources(BRN PRIVATE ${srcs})

target_link_libraries(BRN PRIVATE Qt5::Core)

add_subdirectory(tests)
enable_testing()




