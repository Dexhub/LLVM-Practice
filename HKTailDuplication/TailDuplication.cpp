// Follow the seed and Extend Hot trace until an End statement is reached
// or a Block is encountered that is already in the hottrace vector.
// while visiting each basic block check if the visited block has more than one predecessors,
// If so push the block in stack::tail_successor
// Identify the non-hot predecessor and push it in stack::tail_predecessors

// After the Loop, Things produced are:
// ->>>Hot trace is Generated
// STACK One::merge_blocks-  elements on the trace eligible for tail duplication and
// STACK TWO::merge_predecessors- predecessors of basic blocks from where tail duplication will begin.

// Next Step: For Each element in the Stack Two perform Tail Duplication
// For each element - Clone the entire sub tree
// Use a Stack to keep elements of the else branch of the tree
// Set the predecessor and terminator of each blocks to complete the chain
// Lastly perform Operand Remapping before proceeding with the next block in the tail Stacks

#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Support/CFG.h"
#include <stack>
using namespace llvm;

namespace {

  class TailDuplication : public FunctionPass {
    public:

      static char ID; // Pass identification
      TailDuplication() : FunctionPass(ID) {}
      virtual void getAnalysisUsage(AnalysisUsage &AU) const  {
          //Might have to be changed
          AU.setPreservesAll();
          AU.addRequired<ProfileInfo>();
      }
      virtual bool runOnFunction(Function &f);
      void testTrace();
      void perfTailDupl(Function &f);

    private:
        ProfileInfo *PI;
        std::vector<BasicBlock *> hot_trace;
        std::vector<BasicBlock *> merge_blocks;
        std::vector<BasicBlock *> merge_predecessors;
        //Function F;


};


   bool TailDuplication :: runOnFunction (Function &F) {
        PI = &getAnalysis<ProfileInfo>();
        //std::vector <BasicBlock *> hot_trace;
        //std::vector <BasicBlock *> merge_blocks;
        //std::vector <BasicBlock *> merge_predecessors;

        DEBUG(errs()<<"\n============================= Journey on the Hot trace ===================================\n");
        DEBUG(errs()<<"BasicBlock \t       Execution Count          Predecessors\n");
        DEBUG(errs()<<"==============================================================================================");

        BasicBlock* bb=F.begin();//Setting the Seed.


      while (true)//Come out of the Loop using break whenever a condition for termination is met and the hottrace is formed completely.
          {

            TerminatorInst *term = bb->getTerminator();

            //Print out the name of the basic block, number of instructions, and the Execution count
            DEBUG(errs() << "\n" << bb->getName() << "\t\t\t"<<(int)PI->getExecutionCount(bb)<<"\t\t\t");
            for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI)
              { //Traversing eaich predecessor
                  BasicBlock *Pred = *PI;
                  DEBUG(errs()<<" ;"<<Pred->getName());
              }
            //------------------

            //Special Case If Entry Block
            if (pred_begin(bb)==pred_end(bb))
              {
                  hot_trace.push_back(bb);
                  bb=term->getSuccessor(0);
                  continue;
              }

            else if (term->getNumSuccessors()>1)// If there exists more than one successors
              {

                  //Conditions of different terminator instructions -Switch, Indirect branch, etc will come here.
                    // Check if it has a terminator branch instruction

                    if (isa<BranchInst>(term))
                      { //             BranchInst(TerminatorInst *term, );

                      BasicBlock *BB1=(BasicBlock *) term->getOperand(2);//Compare the Execution Counts of
                      BasicBlock *BB2=(BasicBlock *) term->getOperand(1);//the basic-blocks & select greater

//                              DEBUG(errs()<<"\n---------------------------------------------------------------");
//                              DEBUG(errs()<<"\n BB 1 : "<<BB1->getName()<<"\t Exec Count : "<<(int)PI->getExecutionCount(BB1)
//                              <<"   BB 2 :"<<BB2->getName()<<"\t Exec Count : "<<(int)PI->getExecutionCount(BB2));

                        if (PI->getExecutionCount(BB1) > PI->getExecutionCount(BB2))    // BB1 > BB2
                          {
                            if ((isa<BasicBlock > (BB1->getSinglePredecessor())) && (std::find(hot_trace.begin(), hot_trace.end(),BB1)==hot_trace.end()))
                              {//Check if it has just one predecessor and is not in the hot_trace
                                hot_trace.push_back(bb);
                                bb = *(&BB1);
                                continue;
                              }
                          else
                              {
                                // merge_blocks.push_back(BB1);
                                for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI) //Traversing each predecessor and detect which predecessor is not in Hot trace
                                  {
                                    BasicBlock *Pred = *PI;
                                    if (std::find(hot_trace.begin(), hot_trace.end(),Pred)==hot_trace.end())
                                      {
                                        merge_predecessors.push_back(Pred);
                                        merge_blocks.push_back(bb);
                                        DEBUG(errs()<<"--Merge Block Detected :: "<<bb->getName());
                                        DEBUG(errs()<<":: Predecessor Block ::"<<Pred->getName());
                                      }//If new
                                  }//Traversing Predecessors

                                if (std::find(hot_trace.begin(), hot_trace.end(),BB1)!=hot_trace.end())
                                  {
                                    hot_trace.push_back(bb);
                                    bb = *(&BB1);
                                  }
                                else
                                  {
                                    DEBUG(errs()<<"-->Block Revisited\n---------------------------------------------------------------");
                                    break;
                                  }
                              }//Else isa basic block and hot in trace
                          }//BB1>BB2

                        else            //BB2 > BB1
                          {
                          // Check if BB2 is already in the vector if so, quit the for loop
                          // if (std::find(hot_trace.begin(), hot_trace.end(),BB2)==hot_trace.end()){
                          if ((isa<BasicBlock>(BB2->getSinglePredecessor())) && (std::find(hot_trace.begin(), hot_trace.end(),BB2)==hot_trace.end()))
                            {
                              hot_trace.push_back(bb);
                              bb = *(&BB2);
                              continue;
                            }
                          else
                            {
                            //More than One Predecessor -- Merge Block Detected
                            //----/Check if both the predecessors are not in hot trace.
                              for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI)
                                {
                                //Traversing each predecessor and detect which predecessor is not in Hot trace
                                  BasicBlock *Pred = *PI;
                                  if (std::find(hot_trace.begin(), hot_trace.end(),Pred)==hot_trace.end())
                                    {
                                      merge_predecessors.push_back(Pred);
                                      merge_blocks.push_back(bb);
                                      DEBUG(errs()<<"\n--Merge Block Detected :: "<<bb->getName());
                                      DEBUG(errs()<<"--> Predecessor Block ::"<<Pred->getName());
                                     }//If new
                                }//Traversing Predecessors

                              if (std::find(hot_trace.begin(), hot_trace.end(),BB1)!=hot_trace.end())
                                {
                                  hot_trace.push_back(bb);
                                  bb = *(&BB1);
                                }
                              else
                                {
                                  DEBUG(errs()<<"-->Block Revisited\n---------------------------------------------------------------");
                                  break;
                                }
                            }
                          }   //Else of BB2 > BB1.

                      }//If isa<Branch Instruction>

                    else/*Else of ISA BRANCH inst*/
                      {
                        errs()<<"!!!!!!!!ALERT!!!!!!!!!!UNCAUGHT EXCEPTION";
                      }
                  }//If number of successor greater than 1

              else if (term->getNumSuccessors()==1)
                {
                  //Just one Path , So add the block in hottrace
                  //hot_trace.push_back(bb);
                  if (std::find(hot_trace.begin(), hot_trace.end(),bb)==hot_trace.end())
                    {
                      //DEBUG(errs()<<"Single Path"<<bb->getName());
                      hot_trace.push_back(bb);
                      //---Code to check if this is a Merge Block
                      //++++ Code needs to be added to check if this block is already in the hot trace
                      if (bb->getSinglePredecessor()!=NULL) // one predecessor OR Entry Block (Zero Predecessor)
                        {
                          //  errs()<<"Works when BB is "<<BB2->getName();
                          bb = term->getSuccessor(0);
                          continue;
                        }
                      else
                        {
                          //More than One Predecessor -- Merge Block Detected
                          //----/Check if both the predecessors are not in hot trace.
                          DEBUG(errs()<<"\n--Merge Block Detected :: "<<bb->getName());
                          for (pred_iterator PI = pred_begin(bb), E = pred_end(bb); PI != E; ++PI)
                            {
                              //Traversing each Predecessor
                              // Detect which predecessor is not in Hot trace
                              BasicBlock *Pred = *PI;
                              DEBUG(errs()<<":: Predecessor Block ::"<<Pred->getName());
                              if (std::find(hot_trace.begin(), hot_trace.end(),Pred)==hot_trace.end())
                                {
                                  merge_blocks.push_back(bb);
                                  merge_predecessors.push_back(Pred);
                                } //If new
                            }//Traversing Predecessors
                          bb = term->getSuccessor(0);
                        }
                    }//Block not in hot trace
                  else//Revisited
                    {
                      DEBUG(errs()<<"\n============Revisit Detected=============="<<bb->getName());
                      break;
                    }
                }//If number of Successor is 1
              else if (term->getNumSuccessors()==0)
                {
                  DEBUG(errs()<<"\n============Terminator Block Detected==============");
                  break;
                }
            }//while Loop

//-------Testing Trace----------
          testTrace();
//------------------------------

    //Code for Tail Duplication
          perfTailDupl(F);
    //-------------------------
         return true;
      }

    void TailDuplication::testTrace()
      {

        //------------Hot Trace Formation complete ------
        DEBUG(errs()<<"\n---Hot trace ---\n");
        for ( int i = 0; i< (int)hot_trace.size(); i++)
          DEBUG(errs()<<">>  "<< hot_trace.at(i)->getName() << "  --");
        DEBUG(errs()<<"||");
        DEBUG(errs()<<"\n----------------");
        //-----

        //------------Print Merge Blocks ------
        assert(merge_blocks.size()==merge_predecessors.size());
        DEBUG(errs()<<"\n---Merge Blocks ---\n");
        for ( int i = 0; i<(int)merge_blocks.size(); i++)
          {
            DEBUG(errs()<<"\n>>  "<< merge_blocks.at(i)->getName());
            DEBUG(errs()<<"||"<< merge_predecessors.at(i)->getName());
          }
        DEBUG(errs()<<"\n----------------\n");
        //-----
        //--------------------------------
      }

    void TailDuplication::perfTailDupl(Function &F)
      {
      for (int i=0; i<(int)merge_predecessors.size();i++)
        {
            TerminatorInst *merge_term=merge_predecessors.at(i)->getTerminator();
            BasicBlock* seed= (BasicBlock*) merge_term->getOperand(0);
            std::stack<BasicBlock*> next;
            next.push(seed);

            DEBUG(errs()<<"\nBasic Blocks for Tail Duplication ["<<i<<"] : "<<(merge_predecessors.at(i)->getName()));
            DEBUG(errs()<<"\nTerminator Instruction for this block is "<<*merge_term);

            while (next.size()!=0) //Clone the entire subtree - the Till the Stack is empty.
              {
                  //Method:
                  //Clone the Basic Block
                  //Append ".clone" to the cloned block
                  //Change Operand in Cloned Block %1-->%5
                  //Set predecessor and set Terminator

                  //Take all basic blocks from the Hot Trace + Conditional paths too and Clone them and attach to the outlier

                  ValueToValueMapTy VMap;
                  BasicBlock* contblck = next.top();
                  next.pop();
                  BasicBlock* NewBB = CloneBasicBlock(contblck, VMap, ".clone",&F);

                  //Perform the ReMapping of Clonedinstructions
                  for (BasicBlock::iterator I = NewBB->begin(); I != NewBB->end(); ++I)
                    {
                      //Loop over all the operands of the instruction
                      for (unsigned op=0, E = I->getNumOperands(); op != E; ++op)
                        {
                          const Value *Op = I->getOperand(op);
                          //Get it out of the value map
                          Value *V = VMap[Op];
                          //If not in the value map, then its outside our trace so ignore
                          if(V != 0)
                            I->setOperand(op,V);
                        }
                    }//For Loop Basic Block iterator

                  DEBUG(errs()<<"\nOld Terminator Instruction Operand "<<contblck->getName());

                  merge_term->setOperand(0,NewBB);
                  //     Modify Terminator instruction of the Outlier block, Point it to the new Cloned Block
                  DEBUG(errs()<<"\nContinuing block is "<<contblck->getName());
                  //     Print the Contents of the Cloned Block
                  for(BasicBlock::iterator i = NewBB->begin(), e=NewBB->end(); i!=e ; i++)
                    DEBUG(errs()<<"\nBASIC:"<<*i);

                  //    Code For handling IF, Switch and  other terminator instructions
                  //     Branch statement: push operand 2 first and then operand one.
                  errs()<<"\n";
            }
        }
     }

char TailDuplication::ID = 0;
static RegisterPass<TailDuplication> X("HKtaildupl","------Performs Tail Duplication for Super Block Scheduling ",false,false);
}
