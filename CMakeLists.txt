cmake_minimum_required(VERSION 3.0)

project (bmi-example-c C)

set (CMAKE_C_FLAGS "-ansi -Wall -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2")

find_package(PkgConfig REQUIRED)
pkg_check_modules(BMIC REQUIRED IMPORTED_TARGET bmic)
message("--   bmic include - ${BMIC_INCLUDE_DIRS}")
include_directories(${BMIC_INCLUDE_DIRS})

add_subdirectory (heat)
add_subdirectory (testing)

include (CTest)

