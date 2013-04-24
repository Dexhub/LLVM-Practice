#ifndef HEADER_FILE
#define HEADER_FILE
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Module.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/Compiler.h"
#include "llvm/LLVMContext.h"
#include "llvm/Type.h"
#include "llvm/Constant.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/Twine.h"
#include "llvm/GlobalVariable.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/IRBuilder.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/Twine.h"
#include "llvm/ADT/ilist_node.h"
#include "llvm/GlobalValue.h"
#include "llvm/OperandTraits.h"
#include "llvm//Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Transforms/Instrumentation.h"
#include "llvm/IntrinsicInst.h"
#include "llvm/Assembly/Writer.h"
#include "llvm/Support/Debug.h"
#include "llvm/Function.h"
#include <iostream>
#include "llvm/User.h"
#include "llvm/Operator.h"
#include "llvm/Value.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Analysis/Trace.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Transforms/Utils/Cloning.h"
//using namespace llvm;

namespace{

using namespace llvm;

class TailDuplication: public FunctionPass{
  public:
    static char ID;
    TailDuplication() : FunctionPass(ID){}

    virtual void getAnalysisUsage(AnalysisUsage &AU) const;
    virtual void bool runOnFunction(Function &F);
    static RegisterPass<TailDuplication> X()
    };
}
#endif
