cmake_minimum_required(VERSION 3.10)
project(kasp3)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(client
    src/main_client.cpp
    src/Client.cpp
    src/SocketWrapper.cpp
)

add_executable(processing_server
    src/main_processing.cpp
    src/DataProcessingServer.cpp
    src/SocketWrapper.cpp
)

add_executable(display_server
    src/main_display.cpp
    src/DisplayServer.cpp
    src/SocketWrapper.cpp
)

if(WIN32)
    target_link_libraries(client Ws2_32)
    target_link_libraries(processing_server Ws2_32)
    target_link_libraries(display_server Ws2_32)
endif()

find_package(GTest CONFIG REQUIRED)
if(GTest_FOUND)
    enable_testing()
    add_executable(tests
        tests/test_processing.cpp
        src/DataProcessingServer.cpp
        src/SocketWrapper.cpp
    )
    target_link_libraries(tests GTest::gtest GTest::gtest_main)
    if(WIN32)
        target_link_libraries(tests Ws2_32)
    endif()
    add_test(NAME DataProcessingTest COMMAND tests)
else()
    message(WARNING "gtest not found")
endif()