project(CRS_Server)


set(SOURCE_FILES
        src/CRS_server.c
        src/CRS_router.c
        src/CRS_router.h
)

# Add the library with the specified source files
add_library(CRS_Server STATIC ${SOURCE_FILES})

# Set the include directories
target_include_directories(CRS_Server PRIVATE src/ PUBLIC include/)

target_link_libraries(CRS_Server PRIVATE third_party CRS_Domain CRS_Runner CRS_Common)