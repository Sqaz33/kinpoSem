mkdir build
@REM -создание билда
cmake -S . -B build/
cmake --build build/

@REM -добавление тестового примера
copy test_case/test.xml build
copy test_case/BRN_run.bat build
cd build/Debug
copy BRN.exe ..
