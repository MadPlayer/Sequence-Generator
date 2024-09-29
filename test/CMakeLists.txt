
# cause of cmake download warning
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
  )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_test
  main_test.cc
  )

target_link_libraries(unit_test
  PRIVATE
  # LLVMSupport
  # clangAST
  # clangASTMatchers
  # clangBasic
  # clangFrontend
  # clangSerialization
  # clangTooling
  GTest::gtest_main
  )

include(GoogleTest)
gtest_discover_tests(unit_test)
