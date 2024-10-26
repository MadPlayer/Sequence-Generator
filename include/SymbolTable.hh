#pragma once
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <string_view>
#include <memory>
#include <clang/AST/ASTImporter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/ASTUnit.h>

namespace sequence_gen
{
  class SymbolEntry;

  class SymbolTable
  {
  public:
    SymbolTable(const std::vector<std::string_view>& astFiles);

    std::vector<std::string_view>
    getFileshasMethod(std::string_view methodName) const;

    std::vector<std::string_view>
    getFileshasFunction(std::string_view funcName) const;

  private:
    SymbolEntry* buildEntry(std::string_view astFile, clang::ASTUnit* unit);
    void storeEntry(SymbolEntry* entry);

    // filename -> SymbolEntry
    std::unordered_map<std::string_view, SymbolEntry *> directMap_;

    // method or function name -> SymbolEntry
    std::unordered_map<std::string_view, std::set<SymbolEntry *>> reverseMap_;

    std::vector<std::unique_ptr<SymbolEntry>> allocatedSymbols_;
  };
}    

#endif /* SYMBOLTABLE_H */
