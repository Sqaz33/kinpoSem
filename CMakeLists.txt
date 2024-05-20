cmake_minimum_required(VERSION 3.10)

project(BRN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=================================
# Необходимо добавить qt5 в PATH
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
#=================================

find_package(Qt5 COMPONENTS REQUIRED Core Test)

# ========Настройка для Qt==========
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ==================================


include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

file(GLOB all
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


# Создание исполняемого файла
add_executable(BRN ${all})

# ==========Добавление тестов=========================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        # option(BUILD_TEST "build tests (or no)" ON)
        set(BUILD_TESTS ON)
        if (BUILD_TESTS)
        add_subdirectory(tests)

        # Линк qt для BRN
        target_link_libraries(BRN PUBLIC Qt5::Core Qt5::Test)
        
        enable_testing()
        
        endif()

endif()
# ====================================================




