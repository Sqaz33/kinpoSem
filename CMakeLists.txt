cmake_minimum_required(VERSION 3.10)

# Проект
project(BRN VERSION 0.1 LANGUAGES CXX)

# Минимальный стандтарт языка
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание исполняемого файла
add_executable(BRN)

# Включение заголовочных файлов
target_include_directories(BRN PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Связываем библиотеки Qt
target_link_libraries(BRN PUBLIC "Qt5Core.dll")

# Используем file(GLOB ...) для добавления всех исходных файлов из директории src
file(GLOB_RECURSE ALL_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Указываем исходные файлы для цели BRN
target_sources(BRN PUBLIC ${ALL_SOURCES})

