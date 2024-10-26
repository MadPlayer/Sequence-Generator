#include "MethodScrapper.hh"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace sequence_gen;


class MethodVisitor : public clang::RecursiveASTVisitor<MethodVisitor>
{
public:
  explicit MethodVisitor(std::set<std::string, std::less<>>& methodSet):
    methodSet_{methodSet} {}

  bool VisitCXXMethosDecl(clang::CXXMethodDecl *declaration)
  {
    methodSet_.insert(declaration->getNameAsString());
    return true;
  }

private:
  std::set<std::string, std::less<>>& methodSet_;
};


void MethodScrapper::scrapMethods(std::set<std::string, std::less<>>& methodSet,
                                  clang::ASTUnit* unit)
{
  assert(unit);

  MethodVisitor visitor{methodSet};
  visitor.TraverseAST(unit->getASTContext());
}
