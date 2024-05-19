REM Создание директории build
mkdir build

REM Выполнение CMake конфигурации и сборки
cmake -S . -B build/ ^
&& cmake --build build/ --config Debug

REM Проверка успешности сборки
IF %ERRORLEVEL% NEQ 0 (
    echo Ошибка при сборке проекта.
    exit /b %ERRORLEVEL%
)

REM Добавление тестового примера
copy test_case\test.xml build\test.xml
copy test_case\BRN_run.bat build\BRN_run.bat

REM Переход в директорию Debug и копирование исполняемого файла
cd build\Debug
IF EXIST BRN.exe (
    copy BRN.exe ..
) ELSE (
    echo BRN.exe не найден. Проверьте, что сборка завершилась успешно.
    exit /b 1
)

REM Возвращение в исходную директорию
cd ..