project(CRS_Runner)

set(SOURCE_FILES
        src/CRS_runner.c
        src/CRS_runner_cpp.c
        src/CRS_runner_cpp.h
        src/CRS_runner_python.c
        src/CRS_runner_python.h
        src/CRS_runner.c
        src/CRS_runner_util.h
        src/CRS_runner_util.c
)

add_library(CRS_Runner STATIC ${SOURCE_FILES})

target_include_directories(CRS_Runner PRIVATE src/ PUBLIC include/)

target_link_libraries(CRS_Runner PRIVATE third_party CRS_Common CRS_Domain)