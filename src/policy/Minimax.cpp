#include <cstdlib>
#include<iostream>
#include "../state/state.hpp"
#include "./Minimax.hpp"

using namespace std;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int minimax(State* state, int depth, bool my_turn){
  if(!depth){
    return state->evaluate();
  }
  if(!state->legal_actions.size())
    state->get_legal_actions();
  int value;
  if(my_turn){
    value = -100000;
    for(auto c:state->legal_actions){
      value = max(value,minimax(state->next_state(c),depth-1,false));
    }
    return value;
  }
  else{
    value = 100000;
    for(auto c:state->legal_actions){
      value = min(value,minimax(state->next_state(c),depth-1,true));
    }
    return value;
  }
}

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int max_value=-10000;
  Move max_move;
  int now;
  for(auto c:actions){
    now = minimax(state->next_state(c),depth,false);
    if(now>max_value){
      max_value = now;
      max_move = c;
    }
  }
  return max_move;
}