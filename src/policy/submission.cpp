#include <cstdlib>
#include<iostream>
#include "../state/state.hpp"
#include "./alphabeta.hpp"

using namespace std;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int alphabeta_prun(State* state, int depth, int a, int b, bool my_turn){
    if(!depth)
        return state->evaluate();
    if(!state->legal_actions.size())
        state->get_legal_actions();
    int value;
    if(my_turn){
        value = -10000;
        for(auto c:state->legal_actions){
            value = max(value, alphabeta_prun(state->next_state(c), depth-1, a, b,false));
            a = max(a, value);
            if(a>=b)
                break;
        }
        return a;
    }
    else{
        value = 10000;
        for(auto c:state->legal_actions){
            value = min(value, alphabeta_prun(state->next_state(c), depth-1, a, b, true));
            b = min(b, value);
            if(a>=b){
                break;
            }
        }
        return b;
    }
}

Move alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int max_value=-10000;
  Move max_move;
  int now;
  for(auto c:actions){
    now = alphabeta_prun(state->next_state(c),depth,-10000,10000,false);
    if(now>max_value){
      max_value = now;
      max_move = c;
    }
  }
  return max_move;
}