
ENABLE_TESTING()

INCLUDE(ExternalProject)
EXTERNALPROJECT_ADD(
    GoogleTest
    URL https://github.com/google/googletest/archive/release-1.8.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/googletest
	CMAKE_ARGS -Dgtest_force_shared_crt=ON
    INSTALL_COMMAND ""
)

EXTERNALPROJECT_GET_PROPERTY(GoogleTest source_dir binary_dir)

INCLUDE_DIRECTORIES(
	${source_dir}/googletest/include
    ${CMAKE_SOURCE_DIR}/src
)

SET(TEST_SOURCES
MatrixTest.cpp
VectorTest.cpp)

ADD_EXECUTABLE(UnitTest ${TEST_SOURCES} main.cpp)
ADD_DEPENDENCIES(UnitTest GoogleTest)

TARGET_LINK_LIBRARIES(
	UnitTest 
	debug ${binary_dir}/googlemock/gtest/Debug/${CMAKE_FIND_LIBRARI_PREFIXES}gtest.lib
	optimized ${binary_dir}/googlemock/gtest/Release/${CMAKE_FIND_LIBRARI_PREFIXES}gtest.lib
)
TARGET_LINK_LIBRARIES(
	UnitTest 
	debug ${binary_dir}/googlemock/gtest/Debug/${CMAKE_FIND_LIBRARI_PREFIXES}gtest_main.lib
	optimized ${binary_dir}/googlemock/gtest/Release/${CMAKE_FIND_LIBRARI_PREFIXES}gtest_main.lib
)