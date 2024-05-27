cmake_minimum_required(VERSION 3.22.0)

# CRS = Code Runner Service
project(CRS C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(AppName ${CMAKE_PROJECT_NAME})

set(CRS_APP_DIRECTORY ${CMAKE_SOURCE_DIR}/app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CRS_APP_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CRS_APP_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CRS_APP_DIRECTORY})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CRS_APP_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CRS_APP_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CRS_APP_DIRECTORY})

add_executable(
        ${AppName} main.c
        third_party/src/mongoose.c
        third_party/include/mongoose.h
)

add_subdirectory(third_party)
add_subdirectory(CRS/runner)
add_subdirectory(CRS/server)
add_subdirectory(CRS/common)

target_link_libraries(${AppName} PRIVATE third_party CRS_Runner CRS_Server CRS_Common)
