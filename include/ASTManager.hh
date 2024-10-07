#pragma once
#ifndef ASTMANAGER_H
#define ASTMANAGER_H

#include <clang/AST/ASTImporter.h>
#include <fstream>
#include <string>
#include <vector>

namespace sequence_gen
{
  class ASTManager
  {
  public:
  private:
    ASTManager(const std::vector<std::string>& sources);
    
  };
}

#endif /* ASTMANAGER_H */
