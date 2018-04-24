//===-- Command.cpp -------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Gollvm driver helper class Command methods.
//
//===----------------------------------------------------------------------===//

#include "Command.h"

#include "llvm/Option/ArgList.h"
#include "llvm/Support/Program.h"

namespace gollvm {
namespace driver {

Command::Command(const Action &srcAction,
                 const Tool &creator,
                 const char *executable,
                 llvm::opt::ArgStringList &args)
    : action_(srcAction),
      creator_(creator),
      executable_(executable),
      arguments_(args)
{
}

int Command::execute(std::string *errMsg)
{
  return llvm::sys::ExecuteAndWait(executable_,
                                   arguments_.data(),
                                   /*env=*/nullptr,
                                   /*Redirects*/{},
                                   /*secondsToWait=*/0,
                                   /*memoryLimit=*/0,
                                   errMsg);
}

void Command::print(llvm::raw_ostream &os)
{
  os << executable_;
  for (auto arg : arguments_)
    if (arg != nullptr)
      os << " "  << arg;
  os << "\n";
}

} // end namespace driver
} // end namespace gollvm