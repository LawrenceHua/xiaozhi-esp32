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
set(PROJECT_VER_BASE "2.5.5")
# The trailing segment MUST be monotonic. A sha-derived segment is unique per
# commit but not ordered, so a descendant commit can decode BELOW the running
# firmware; the server then offers it and the device answers "Current is the
# latest version" - a silent no-op that looks like a healthy check.
# The counter is the CI run number (or VERSION_COUNTER for a manual build), and
# publish-fw.sh refuses any version that is not strictly greater than what is
# already deployed, so a stale counter fails loudly instead of silently.
if(DEFINED ENV{VERSION_COUNTER} AND NOT "$ENV{VERSION_COUNTER}" STREQUAL "")
    set(VER_COUNTER "$ENV{VERSION_COUNTER}")
elseif(DEFINED ENV{GITHUB_RUN_NUMBER} AND NOT "$ENV{GITHUB_RUN_NUMBER}" STREQUAL "")
    set(VER_COUNTER "$ENV{GITHUB_RUN_NUMBER}")
else()
    message(FATAL_ERROR
        "VERSION_COUNTER is not set. Refusing to build firmware with an ambiguous version. "
        "Export VERSION_COUNTER=<monotonic integer> (CI sets it from GITHUB_RUN_NUMBER) and rebuild.")
endif()
# GIT_SHA is still mandatory: the version no longer carries it, so the manifest is
# the only thing tying an artifact back to a commit.
if(DEFINED ENV{GIT_SHA} AND NOT "$ENV{GIT_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GIT_SHA}" 0 6 GIT_SHA6)
elseif(DEFINED ENV{GITHUB_SHA} AND NOT "$ENV{GITHUB_SHA}" STREQUAL "")
    string(SUBSTRING "$ENV{GITHUB_SHA}" 0 6 GIT_SHA6)
else()
    message(FATAL_ERROR
        "GIT_SHA is not set. Refusing to build firmware that cannot be traced to a commit. "
        "Export GIT_SHA=<commit sha> (CI sets it from github.sha) and rebuild.")
endif()
set(PROJECT_VER "${PROJECT_VER_BASE}.${VER_COUNTER}")
message(STATUS "xiaozhi firmware version: ${PROJECT_VER} (counter ${VER_COUNTER}, sha ${GIT_SHA6})")
project(xiaozhi)
