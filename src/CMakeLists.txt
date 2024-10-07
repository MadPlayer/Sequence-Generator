set(LLVM_LINK_COMPONENTS
  Support
  )

include_directories(PRIVATE
  ${CLANG_INCLUDE_DIRS}
  ${LLVM_INCLUDE_DIRS}
  )

add_executable(main
  main.cc
  ProtoVisitor.cc
  )

target_link_libraries(main
  PRIVATE
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )
