#pragma once
#ifndef METHODSCRAPPER_H
#define METHODSCRAPPER_H

#include <clang/Frontend/FrontendAction.h>
#include <set>
#include <string>


namespace sequence_gen
{
  class MethodScrapper
  {
  public:
    MethodScrapper() = default;

    // scraps methods with implementation. (declaration)
    void scrapMethods(std::set<std::string, std::less<>>& methodSet, clang::ASTUnit* unit);
  };
}

#endif /* METHODSCRAPPER_H */
