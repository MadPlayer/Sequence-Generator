#ifndef PROTOVISITOR_H
#define PROTOVISITOR_H

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

namespace proto {

class ProtoVisitor : public clang::RecursiveASTVisitor<ProtoVisitor> {
public:
  explicit ProtoVisitor() = default;

  bool VisitCXXMethodDecl(clang::CXXMethodDecl *declaration);
  bool VisitCXXMemberCallExpr(clang::CXXMemberCallExpr *memberCall);
  bool VisitIfStmt(clang::IfStmt *ifStmt);
  bool VisitForStmt(clang::ForStmt *forStmt);
  bool VisitWhileStmt(clang::WhileStmt *whileStmt);
};

}


#endif /* PROTOVISITOR_H */
