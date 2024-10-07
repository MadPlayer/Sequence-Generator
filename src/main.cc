#include <clang/Serialization/ASTReader.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/Serialization/PCHContainerOperations.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Basic/DiagnosticIDs.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <memory>
#include <iostream>
#include "ProtoVisitor.hh"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
  clang::CompilerInstance CI;
  CI.createDiagnostics();
  auto TO = std::make_shared<clang::TargetOptions>();
  TO->Triple = "x86_64-pc-linux-gnu";
  CI.setTarget(clang::TargetInfo::CreateTargetInfo(CI.getDiagnostics(), TO));

  auto unit =
    clang::ASTUnit::LoadFromASTFile("ClassA.ast",
                                    CI.getPCHContainerReader(),
                                    clang::ASTUnit::WhatToLoad::LoadASTOnly,
                                    &CI.getDiagnostics(),
                                    CI.getFileSystemOpts(),
                                    CI.getHeaderSearchOptsPtr());
  auto unit_b =
    clang::ASTUnit::LoadFromASTFile("ClassB.ast",
                                    CI.getPCHContainerReader(),
                                    clang::ASTUnit::WhatToLoad::LoadASTOnly,
                                    &CI.getDiagnostics(),
                                    CI.getFileSystemOpts(),
                                    CI.getHeaderSearchOptsPtr());

  if (unit)
    {
      std::cout << "unit is valied\n";
      proto::ProtoVisitor visitor;
      visitor.TraverseAST(unit->getASTContext());
    }
  if (unit_b)
    {
      std::cout << "unit B is valied\n";
      proto::ProtoVisitor visitor;
      visitor.TraverseAST(unit_b->getASTContext());
    }
  
  return 0;
}
