cmake_minimum_required(VERSION 3.10)

project(BRN VERSION 0.1)

# Создание исполняемого файла
add_executable(BRN)

# Включение заголовочных файлов
target_include_directories(BRN PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Используем file(GLOB ...) для добавления всех исходных файлов из директории src
file(GLOB_RECURSE ALL_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Указываем исходные файлы для цели BRN
target_sources(BRN PUBLIC ${ALL_SOURCES})