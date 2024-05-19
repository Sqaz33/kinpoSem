cmake_minimum_required(VERSION 3.10)

if (WIN32)

project(BRN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание исполняемого файла
add_executable(BRN)

#=================================
# Необходимо добавить qt5 в PATH
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
#=================================

find_package(Qt5 COMPONENTS Core Test REQUIRED)

# ========Настройка для Qt==========
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ==================================


# ==========Включение файлов проекта для BRN==========
target_include_directories(
    BRN PUBLIC "${PROJECT_SOURCE_DIR}/include"
)
file(
    GLOB_RECURSE 
    SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
target_sources(BRN PUBLIC ${SOURCES})
# ====================================================

# ==========Добавление тестов=========================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        # option(BUILD_TEST "build tests (or no)" ON)
        set(BUILD_TESTS ON)

        if (BUILD_TESTS)
                add_subdirectory(tests)
        endif()

endif()
# ====================================================

# Линк qt для BRN
target_link_libraries(BRN PUBLIC Qt5::Core)

else()
    message("Приложение только для платформы WIN32")
endif()