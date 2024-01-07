
#include "llvm/Analysis/CFGPrinter.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {

class ExamplePass : public ModulePass {

 public:
  static char ID;
  ExamplePass() : ModulePass(ID) { }
  
  bool doInitialization(Module &M) override;
  bool runOnModule(Module &M) override;

};

}  // namespace

char ExamplePass::ID = 0;

bool ExamplePass::doInitialization(Module &M) {

  return true;

}

bool ExamplePass::runOnModule(Module &M) {
  
  errs() << "runOnModule\n";

  

  for (auto &F : M) {
        errs() << F.getName() << "\n";

  //       for (auto &B : F) {
  //           B.dump();

  //           for (auto &I : B) {
  //               I.dump();
  //           }
  //       }
    }

 
  //1
  IntegerType *Int32Ty = IntegerType::getInt32Ty(M.getContext());
  Type *VoidTy = Type::getVoidTy(M.getContext());
  //get "debug" function
  FunctionType *FnTy = FunctionType::get(VoidTy, {Int32Ty}, false);
  FunctionCallee Fn_debug = M.getOrInsertFunction("debug", FnTy);
  //get "main" function enter point
  Function *Fn_main = M.getFunction("main");
  BasicBlock &entryBlock = Fn_main->getEntryBlock();
  BasicBlock::iterator IP = entryBlock.getFirstInsertionPt();
  //call "debug" function
  IRBuilder<> IRB(&(*IP));
  IRB.CreateCall(Fn_debug, ConstantInt::get(Int32Ty, 9527));

  //2
  Fn_main->getArg(0)->replaceAllUsesWith(ConstantInt::get(Int32Ty, 9487));
  
  //3
  IntegerType *Int8Ty = IntegerType::getInt8Ty(M.getContext());
  
  Value *index = IRB.CreateGEP(Fn_main->getArg(1), ConstantInt::get(Int8Ty, 1));

  Value *str = IRB.CreateGlobalStringPtr("aesophor is ghost !!!");
  IRB.CreateStore(str, index);



  return true;
  
}

static void registerExamplePass(const PassManagerBuilder &,
                                           legacy::PassManagerBase &PM) {

  PM.add(new ExamplePass());

}

static RegisterStandardPasses RegisterExamplePass(
    PassManagerBuilder::EP_OptimizerLast, registerExamplePass);

static RegisterStandardPasses RegisterExamplePass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerExamplePass);

