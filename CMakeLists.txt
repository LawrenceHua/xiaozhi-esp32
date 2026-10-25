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
# The version must identify the build: <base>-<sha>. The sha comes from CI because
# git is not usable inside the espressif/idf build container. Missing sha is a hard
# error on purpose - an unversioned image in an OTA slot produces upgrades that
# report success and change nothing.
if(DEFINED ENV{GIT_SHA} AND NOT "$ENV{GIT_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GIT_SHA}" 0 7 GIT_SHA_SHORT)
elseif(DEFINED ENV{GITHUB_SHA} AND NOT "$ENV{GITHUB_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GITHUB_SHA}" 0 7 GIT_SHA_SHORT)
else()
    message(FATAL_ERROR
        "GIT_SHA is not set. Refusing to build firmware with an ambiguous version. "
        "Export GIT_SHA=<commit sha> (CI sets it from github.sha) and rebuild.")
endif()
set(PROJECT_VER "${PROJECT_VER_BASE}-${GIT_SHA_SHORT}")
message(STATUS "xiaozhi firmware version: ${PROJECT_VER}")
project(xiaozhi)
