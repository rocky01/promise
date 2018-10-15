find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "release-1.8.1"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

ExternalProject_Get_Property(gtest source_dir)
set(GTEST_SOURCE_DIR ${source_dir})
