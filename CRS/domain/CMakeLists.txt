project(CRS_Domain)

set(SOURCE_FILES
        src/CRS_domain.c
)

# Add the library with the specified source files
add_library(CRS_Domain STATIC ${SOURCE_FILES})

# Set the include directories
target_include_directories(CRS_Domain PRIVATE src/ PUBLIC include/)