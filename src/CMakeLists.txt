add_library(AwesomePrefixCheck SHARED "")
target_compile_options(AwesomePrefixCheck PRIVATE -fno-rtti)
target_include_directories(AwesomePrefixCheck
    PRIVATE
        ${CLANG_INCLUDE_DIRS}
        ${LLVM_INCLUDE_DIRS}
)
target_sources(AwesomePrefixCheck PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/AwesomePrefixCheck.cpp)
