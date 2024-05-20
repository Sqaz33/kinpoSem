# В директории tests/CMakeLists.txt

# Найти библиотеки Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Test)

# Создание исполняемого файла с тестами
add_executable(tst BigRealNumberTests.cpp)

# Линковка тестового исполняемого файла с библиотеками Qt5
target_link_libraries(tst Qt5::Core Qt5::Test)

# Регистрация теста в CTest
add_test(NAME MyTestClass COMMAND tst)