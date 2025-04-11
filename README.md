Запуск

1) Скачать Googletest

cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=E:\googletesttsts\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build .
cd build\Debug

2) Тесты:
.\tests.exe

3) Основная часть:
.\display_server.exe 8082
.\processing_server.exe 8081 127.0.0.1 8082
.\client.exe 127.0.0.1 8081