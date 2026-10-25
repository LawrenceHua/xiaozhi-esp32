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
# Version must be build-unique AND parseable by Ota::ParseVersion, which splits on
# '.' and requires every segment numeric - a hex sha there is discarded outright
# ("invalid version segment"), so the device would ignore the upgrade. Encode the
# sha as a decimal integer: 2.5.4.<int(sha[:6],16)>. Two different commits cannot
# collide; rebuilding the same commit reproduces the same number, which is correct
# (same source -> same version).
if(DEFINED ENV{GIT_SHA} AND NOT "$ENV{GIT_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GIT_SHA}" 0 6 GIT_SHA6)
elseif(DEFINED ENV{GITHUB_SHA} AND NOT "$ENV{GITHUB_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GITHUB_SHA}" 0 6 GIT_SHA6)
else()
    message(FATAL_ERROR
        "GIT_SHA is not set. Refusing to build firmware with an ambiguous version. "
        "Export GIT_SHA=<commit sha> (CI sets it from github.sha) and rebuild.")
endif()
math(EXPR GIT_SHA_DEC "0x${GIT_SHA6}" OUTPUT_FORMAT DECIMAL)
set(PROJECT_VER "${PROJECT_VER_BASE}.${GIT_SHA_DEC}")
message(STATUS "xiaozhi firmware version: ${PROJECT_VER} (sha ${GIT_SHA6})")
project(xiaozhi)
