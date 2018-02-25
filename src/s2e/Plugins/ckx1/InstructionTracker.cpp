#include<s2e/S2E.h>
#include "InstructionTracker.h"
#include<s2e/Utils.h>
namespace s2e{
  namespace plugins{
    S2E_DEFINE_PLUGIN(InstructionTracker,
                      "Tutorial - Tracking instructions",
                      "InstructionTracker",
                    );
    void InstructionTracker::initialize(){
      s2e()->getDebugStream() << "CKX: BEGINNING ROLLING ... "<< "\n";
      m_address = (uint64_t) s2e()->getConfig()->getInt(getConfigKey()+".addressToTrack");
      s2e()->getCorePlugin()->onTranslateInstructionStart.connect(
        sigc::mem_fun(*this,&InstructionTracker::onTranslateInstruction)
      );}
    void InstructionTracker::onTranslateInstruction(ExecutionSignal *signal,
                                                    S2EExecutionState *state,
                                                  TranslationBlock *tb,
                                                uint64_t pc){
        if(m_address == pc){
          signal->connect(sigc::mem_fun(*this,&InstructionTracker::onInstructionExecution));
        }
                                                }
   void InstructionTracker::onInstructionExecution(S2EExecutionState *state, uint64_t pc){
         DECLARE_PLUGINSTATE(InstructionTrackerState, state);
     s2e()->getDebugStream() << "Execution instruction at " << hexval(pc) << "\n";
      plgState->increment();

      if ((plgState->get() % 2) == 0) {
       onPeriodicEvent.emit(state, pc);
   }

   }

    }
  }
