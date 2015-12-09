#ifndef __CONVERTER__
#define __CONVERTER__
#include "NFAMachine.hpp"
NFAMachine::NFAInstance* GetDFAFromNFA(NFAMachine::NFAInstance instance);
NFAMachine::NFAInstance* MinimizeDFA(NFAMachine::NFAInstance instance);
#endif