#include <clang/AST/ASTImporter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Tooling/Tooling.h>
#include <fstream>
#include <string>
#include <string_view>
#include <memory>
#include <iostream>

#include "ProtoVisitor.hh"

using namespace clang;
using namespace tooling;
using namespace ast_matchers;

template <typename Node, typename Matcher>
Node *getFirstDecl(Matcher M, const std::unique_ptr<ASTUnit>& Unit)
{
  auto MB = M.bind("bindStr");
  auto MatchRes = match(MB, Unit->getASTContext());
  assert(MatchRes.size() >= 1);
  Node *Result =
    const_cast<Node *>(MatchRes[1].template getNodeAs<Node>("bindStr"));
  assert(Result);
  return Result;
}

std::unique_ptr<ASTUnit> buildASTFromFile(std::string_view file_name) {
  std::ifstream source{file_name.data()};
  std::string code{std::istreambuf_iterator<char>(source),
                   std::istreambuf_iterator<char>()};
  std::unique_ptr<ASTUnit> unit = buildASTFromCode(code, file_name.data());
  return unit;
}

int main(int argc, const char **argv)
{
  auto unit_A = buildASTFromFile("ClassA.cc");
  auto unit_B = buildASTFromFile("ClassB.cc");

  auto Matcher = cxxMethodDecl(hasName("ClassB::method1"));
  auto *From = getFirstDecl<CXXMethodDecl>(Matcher, unit_B);
  ASTImporter Importer(unit_A->getASTContext(), unit_A->getFileManager(),
                       unit_B->getASTContext(), unit_B->getFileManager(), true);
  llvm::Expected<Decl *> ImportedOrErr = Importer.Import(From);
  if (!ImportedOrErr)
    {
      llvm::Error Err = ImportedOrErr.takeError();
      llvm::errs() << "ERROR: " << Err << '\n';
      llvm::consumeError(std::move(Err));
      return 1;
    }
  Decl *Imported = *ImportedOrErr;
  Imported->getTranslationUnitDecl()->dumpColor();

  std::cout << " ================ Visitor Output Below! ==============\n";

  proto::ProtoVisitor visitor;
  visitor.TraverseAST(Imported->getASTContext());

  return 0;
}
