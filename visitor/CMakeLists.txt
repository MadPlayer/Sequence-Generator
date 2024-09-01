set(LLVM_LINK_COMPONENTS
  Support
  )

include_directories(PRIVATE
  ${CLANG_INCLUDE_DIRS}
  ${LLVM_INCLUDE_DIRS}
  )

add_executable(find-class-decls FindClassDecls.cc)
target_link_libraries(find-class-decls
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )

add_executable(astimporter-demo ASTImporterDemo.cc)
target_link_libraries(astimporter-demo
  PRIVATE
  LLVMSupport
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )
