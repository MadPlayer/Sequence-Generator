#include <string>
#include <set>
#include <utility>
#include "SymbolTable.hh"
#include "MethodScrapper.hh"

using namespace sequence_gen;

class sequence_gen::SymbolEntry
{
public:
  SymbolEntry(std::string fileName, clang::ASTUnit *unit):
    fileName_{fileName}
  {
    assert(unit);
    MethodScrapper scrapper;
    scrapper.scrapMethods(methodList_, unit);
  }

  std::string_view getName() const
  {
    return std::string_view{fileName_};
  }

  bool hasMethod(std::string_view methodName) const
  {
    return methodList_.contains(methodName);
  }

  bool hasFunction(std::string_view functionName) const
  {
    return functionList_.contains(functionName);
  }

private:
  friend class SymbolTable;
  std::string fileName_;
  std::set<std::string, std::less<>> methodList_;
  std::set<std::string, std::less<>> functionList_;
};


SymbolTable::SymbolTable(const std::vector<std::string_view> &astFiles)
{
  for (auto fileName : astFiles)
    {
      auto* symbol = buildEntry(fileName);
      if (symbol != nullptr)
        {
          storeEntry(symbol);
        }
    }
}

std::vector<std::string_view>
SymbolTable::getFileshasMethod(std::string_view methodName) const
{
  std::vector<std::string_view> fileList;
  if (auto entryList = reverseMap_.find(methodName); entryList != reverseMap_.cend())
    {
      for (auto* entry : entryList->second)
        {
          fileList.push_back(entry->getName());
        }
    }
  return fileList;
}

std::vector<std::string_view>
SymbolTable::getFileshasFunction(std::string_view funcName) const
{
  // for now, don't distinguish between functions and methods
  return getFileshasMethod(funcName);
}

void SymbolTable::storeEntry(SymbolEntry* entry)
{
  assert(entry);
  directMap_.insert(std::make_pair(entry->getName(), entry));
  for (auto& method : entry->methodList_)
    {
      reverseMap_[method].insert(entry);
    }
}

SymbolEntry* SymbolTable::buildEntry(std::string_view astFile, clang::ASTUnit* unit)
{
  auto entry = std::make_unique<SymbolEntry>(std::string(astFile), unit);
  allocatedSymbols_.emplace_back(std::move(entry));
  return allocatedSymbols_.back().get();
}
