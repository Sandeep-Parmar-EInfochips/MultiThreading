cmake_minimum_required(VERSION 3.0)

project(Multithreading)
set(PROJECT_NAME Multithreading)

find_package(UnitTest++ REQUIRED)

include_directories(${UTPP_INCLUDE_DIRS})

if(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")
else(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")
set(CMAKE_CXX_FLAGS "-std=gnu++11")
endif(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")

if(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin/windows)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/windows)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/windows)
else(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin/linux)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/linux)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/linux)
endif(${CMAKE_C_FLAGS} MATCHES "_WINDOWS")


include_directories(inc)
file(GLOB HEADERS "inc/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} pthread UnitTest++)
