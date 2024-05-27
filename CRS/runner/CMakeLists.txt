project(CRS_Runner)

set(SOURCE_FILES
        src/CRS_Runner.c
)

# Add the library with the specified source files
add_library(CRS_Runner STATIC ${SOURCE_FILES})

# Set the include directories
target_include_directories(CRS_Runner PRIVATE src/ PUBLIC include/)

target_link_libraries(CRS_Runner PRIVATE third_party CRS_Common CRS_Domain)