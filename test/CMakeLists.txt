file(GLOB_RECURSE T_SRCS *.cpp)
file(GLOB_RECURSE T_HEADERS *.hpp)

file(GLOB_RECURSE L_SRCS "${LIB_DIR}/*.cpp")
file(GLOB_RECURSE L_HEADERS "${LIB_DIR}/*.hpp")

add_executable(testPromises ${T_SRCS} ${T_HEADERS} ${L_HEADERS} ${L_SRCS})

include(gtest.cmake)

include_directories("${GTEST_SOURCE_DIR}/googletest/include"
                    "${GTEST_SOURCE_DIR}/googlemock/include"
                    "${LIB_DIR}"
                    "${TST_DIR}")

target_link_libraries(testPromises
    libgtest
    libgmock
)

add_test(NAME testPromises
         COMMAND testPromises)
