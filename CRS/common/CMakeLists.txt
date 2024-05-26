project(CRS_Common)

set(SOURCE_FILES
        src/CRS_Common.c
)

# Add the library with the specified source files
add_library(CRS_Common STATIC ${SOURCE_FILES})

# Set the include directories
target_include_directories(CRS_Common PRIVATE src/ PUBLIC include/)