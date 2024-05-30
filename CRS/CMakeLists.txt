project(CRS_Root)

add_library(CRS_Root
        common/CRS_common.c
        common/CRS_common.h
        domain/CRS_domain.c
        domain/CRS_domain.h
        runner/CRS_runner.c
        runner/CRS_runner.h
        runner/CRS_runner_cpp.c
        runner/CRS_runner_cpp.h
        runner/CRS_runner_python.c
        runner/CRS_runner_python.h
        runner/CRS_runner_util.c
        runner/CRS_runner_util.h
        server/CRS_router.c
        server/CRS_router.h
        server/CRS_server.c
        server/CRS_server.h
)

target_include_directories(CRS_Root PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(CRS_Root third_party)

