cmake_minimum_required(VERSION 3.10)

find_package(Qt5 REQUIRED COMPONENTS Core Test)

add_executable(tst)

target_sources(
    tst PRIVATE
    BigRealNumberTests.cpp
    ActionsFromXMLTests.cpp
    testInstruments.cpp
    tests_main.cpp
)
target_include_directories(tst PRIVATE 
    testInstruments.h 
    BigRealNumberTests.h
    ActionsFromXMLTests.h
)

target_sources(
    tst PRIVATE
    "${PROJECT_SOURCE_DIR}/src/BigRealNumber.cpp"
    "${PROJECT_SOURCE_DIR}/src/ActionError.cpp"
    "${PROJECT_SOURCE_DIR}/src/Action.cpp"
    "${PROJECT_SOURCE_DIR}/src/StdStringsToTxt.cpp"
    "${PROJECT_SOURCE_DIR}/src/ActionsFromXML.cpp"
)

target_link_libraries(tst PRIVATE Qt5::Core Qt5::Test)

add_test(NAME tsts COMMAND tst)