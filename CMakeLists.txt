# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# Add this line to disable the specific warning
add_compile_options(-Wno-missing-field-initializers)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# "Trim" the build. Include the minimal set of components, main, and anything it depends on.
idf_build_set_property(MINIMAL_BUILD ON)

# Version shown by the device and compared by the OTA server: numeric base first
# (that is what decides "newer"), then the git sha so two builds can never claim
# the same version. Falls back to the bare base when git is unavailable.
set(PROJECT_VER_BASE "2.5.4")
execute_process(
    COMMAND git rev-parse --short=7 HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    RESULT_VARIABLE GIT_RC)
if(GIT_RC EQUAL 0 AND GIT_SHA)
    set(PROJECT_VER "${PROJECT_VER_BASE}-${GIT_SHA}")
else()
    set(PROJECT_VER "${PROJECT_VER_BASE}")
endif()
message(STATUS "xiaozhi firmware version: ${PROJECT_VER}")
project(xiaozhi)
