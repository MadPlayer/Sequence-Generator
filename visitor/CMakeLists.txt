set(LLVM_LINK_COMPONENTS
  Support
  )

add_executable(find-class-decls FindClassDecls.cc)
target_include_directories(find-class-decls
    PRIVATE
        ${CLANG_INCLUDE_DIRS}
        ${LLVM_INCLUDE_DIRS}
)

target_link_libraries(find-class-decls
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )
