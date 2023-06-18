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
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int max_value=0;
  Move max_move;
  int now;
  for(auto c:actions){
    now = state->next_state(c)->evaluate();
    cout<<"value: "<<now<<endl;
    cout<<"max: "<<max_value<<endl;
    if(now>max_value){
      max_value = now;
      max_move = c;
    }  
  }
  return max_move;
}