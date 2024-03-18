cmake_minimum_required(VERSION 3.5.0)
project(design VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

aux_source_directory(./source SourceFile)
add_executable(design ${SourceFile})

set(CMAKE_BUILD_TYPE "Debug")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
