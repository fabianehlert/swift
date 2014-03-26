//===--- Link.cpp - Link in transparent SILFunctions from module ----------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "link"
#include "swift/SILPasses/Passes.h"
#include "swift/AST/Module.h"
#include "swift/Serialization/SerializedSILLoader.h"
#include "swift/SIL/SILExternalSource.h"
#include "swift/SIL/SILModule.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CommandLine.h"

using namespace swift;

//===----------------------------------------------------------------------===//
//                          Top Level Driver
//===----------------------------------------------------------------------===//

void swift::performSILLinking(SILModule *M, bool LinkAll) {
  auto LinkMode = LinkAll? SILModule::LinkingMode::LinkAll :
    SILModule::LinkingMode::LinkNormal;
  for (auto &Fn : *M)
    M->linkFunction(&Fn, LinkMode);

  if (!LinkAll)
    return;

  M->linkAllWitnessTables();
  M->linkAllVTables();
}


