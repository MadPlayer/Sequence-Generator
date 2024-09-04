#include "ProtoVisitor.hh"
#include <iostream>

using namespace proto;
using namespace clang;

void Print(Stmt* stmt)
{
  std::string buf;
  llvm::raw_string_ostream os{buf};
  stmt->printPrettyControlled(os, nullptr, PrintingPolicy{LangOptions{}});
  std::cout << buf << '\n';
}

bool ProtoVisitor::VisitCXXMethodDecl(CXXMethodDecl *declaration)
{
  if (declaration->isFirstDecl())
    {
      std::cout << "I needs the declaration with implementation\n";
      return true;
    }
  if (declaration->getParent()->getNameAsString() != "ClassA")
    {
      std::cout << "class name mismatch: "
                << declaration->getParent()->getNameAsString() << '\n';
      return true;
    }
  if (declaration->getNameAsString() != "callB")
    {
      std::cout << "mismatch method name: "
                << declaration->getNameAsString() << '\n';
      return true;
    }

  declaration->getCanonicalDecl()->dumpColor();
  return true;
}


bool ProtoVisitor::VisitCXXMemberCallExpr(clang::CXXMemberCallExpr *memberCall)
{
  memberCall->getMethodDecl()->dumpColor();
  return true;
}

bool ProtoVisitor::VisitIfStmt(clang::IfStmt *ifStmt)
{
  ifStmt->getCond()->dumpColor();
  Print(ifStmt->getCond());
  return true;
}

bool ProtoVisitor::VisitForStmt(clang::ForStmt *forStmt)
{
  forStmt->getCond()->dumpColor();
  Print(forStmt->getCond());
  return true;
}

bool ProtoVisitor::VisitWhileStmt(clang::WhileStmt *whileStmt)
{
  whileStmt->getCond()->dumpColor();
  Print(whileStmt->getCond());
  return true;
}
