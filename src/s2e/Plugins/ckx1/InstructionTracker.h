#ifndef S2E_PLUGINS_INSTRTRACKER_H
#define S2E_PLUGINS_INSTRTRACKER_H


//in libs2ecore
#include<s2e/Plugin.h>
#include<s2e/CorePlugin.h>
#include<s2e/S2EExecutionState.h>


namespace s2e{
  namespace plugins{
    class InstructionTracker : public Plugin
    {
      S2E_PLUGIN
    public:
      InstructionTracker(S2E *s2e): Plugin(s2e){}
      void initialize();
      void onTranslateInstruction(ExecutionSignal *signal,
                                                      S2EExecutionState *state,
                                                    TranslationBlock *tb,
                                                  uint64_t pc);
      void onInstructionExecution(S2EExecutionState *state, uint64_t pc);
    private:
      uint64_t m_address;



    public:
      sigc::signal<void,
                 S2EExecutionState *, // The first parameter of the callback is the state
                 uint64_t             // The second parameter is an integer representing the program counter
                > onPeriodicEvent;
    };


//ckx: can't understand ....
    class InstructionTrackerState: public PluginState{
    private:
      int m_count;
    public:
      InstructionTrackerState(){
        m_count=0;
    }
    virtual ~InstructionTrackerState(){}
    static PluginState *factory(Plugin*,S2EExecutionState*){
      return new InstructionTrackerState();
    }
    InstructionTrackerState *clone() const{
      return new InstructionTrackerState(*this);
    }
    void increment(){
      ++m_count;
    }
    int get(){
      return m_count;
    }
  };
}
}

#endif
