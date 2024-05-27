project(third_party)

set(SOURCE_FILES
        src/mongoose.c
)

# Add the library with the specified source files
add_library(third_party STATIC ${SOURCE_FILES})

# Set the include directories
target_include_directories(third_party PRIVATE src/ PUBLIC include/)