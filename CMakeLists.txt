cmake_minimum_required(VERSION 3.10)

if (WIN32)

project(BRN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание исполняемого файла
add_executable(BRN)

#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5Core REQUIRED)

# ==========Включение файлов проекта=========
target_include_directories(
    BRN PUBLIC "${PROJECT_SOURCE_DIR}/include"
)
file(
    GLOB_RECURSE 
    SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
target_sources(BRN PUBLIC ${SOURCES})
# ===========================================

# Линк qt
target_link_libraries(BRN Qt5::Core)

else()
    message("Приложение только для платформы WIN32")
endif()