#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};

int value_list(int type){
  switch (type)  //1=pawn, 2=rook, 3=knight, 4=bishop, 5=queen, 6=king
  {
  case 1:
    return 10;
  case 2:
    return 50;
  case 3:
    return 30;
  case 4:
    return 30;
  case 5:
    return 90;
  default:
    return 900;
  }
}

/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){   //0=empty, 1=pawn, 2=rook, 3=knight, 4=bishop, 5=queen, 6=king
  // [TODO] design your own evaluation function
  int my_value =0;
  int opponent_value =0;  //value: pawn = 10, rook = 50, bishop = 30, knight = 30
  int now;                     // queen = 90, king = 900
  int a,b,temp,max=0;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  for(int i=0; i<BOARD_H; i+=1){ //calculate my value
    for(int j=0; j<BOARD_W; j+=1){
      if((now=self_board[i][j])){
        switch(now){
          case 1:      //pawn
            if(!this->player){ //white
              if(i==1)          // promote
                my_value+=35;
              else
                my_value+=5;
              max=0;
              if(i-1>=0&&i-1<6){
                if(j+1>=0&&j+1<5){
                  if(oppn_board[i-1][j+1]){
                    max = value_list(oppn_board[i-1][j+1]);
                  }
                }
                if(j-1>=0&&j-1<5){
                  if(oppn_board[i-1][j-1]){
                    temp = value_list(oppn_board[i-1][j-1]);
                    max = temp>max?temp:max;
                  }
                }
              }
              my_value+=max;
            }
            else{
              if(i==4)
                my_value+=35;
              else  
                my_value+=5;
              max=0;
              if(i+1>=0&&i+1<6){
                if(j+1>=0&&j+1<5){
                  if(oppn_board[i+1][j+1]){
                    max = value_list(oppn_board[i+1][j+1]);
                  }
                }
                if(j-1>=0&&j-1<5){
                  if(oppn_board[i+1][j-1]){
                    temp = value_list(oppn_board[i+1][j-1]);
                    max = temp>max?temp:max;
                  }
                }
              }
              my_value+=max;
            }
            break;
          case 2:
            my_value+=50;
            //int a,b,temp,max=0;
            max=0;
            for(int x=0;x<=3;x++){
              for(int y=0;y<=6;y++){
                a = i+move_table_rook_bishop[x][y][0];
                b = j+move_table_rook_bishop[x][y][1];
                if(a>=0&&a<6&&b>=0&&b<5){
                  if(self_board[a][b])
                    break;
                  if(oppn_board[a][b]){
                    temp = value_list(oppn_board[a][b]);
                    max = temp>max?temp:max;
                    break;
                  }
                }
                else{
                  break;
                }
              }
            }
            my_value+=max;
            break;
          case 3:
            my_value+=30;
            //int a,b,temp,max=0;
            max=0;
            for(int x=0;x<=7;x++){
              a = i + move_table_knight[x][0];
              b = j + move_table_knight[x][1];
              if(a>=0&&a<6&&b>=0&&b<5){
                if(oppn_board[a][b]){
                  temp = value_list(oppn_board[a][b]);
                  max = temp>max?temp:max;
                }
              }
            }
            my_value+=max;
            break;
          case 4:
            my_value+=30;
            //int a,b,temp,max=0;
            max=0;
            for(int x=4;x<=7;x++){
              for(int y=0;y<=6;y++){
                a = i+move_table_rook_bishop[x][y][0];
                b = j+move_table_rook_bishop[x][y][1];
                if(a>=0&&a<6&&b>=0&&b<5){
                  if(self_board[a][b])
                    break;
                  if(oppn_board[a][b]){
                    temp = value_list(oppn_board[a][b]);
                    max = temp>max?temp:max;
                    break;
                  }
                }
                else{
                  break;
                }
              }
            }
            my_value+=max;
            break;
          case 5:
            my_value+=90;
            //int a,b,temp,max=0;
            max=0;
            for(int x=0;x<=7;x++){
              for(int y=0;y<=6;y++){
                a = i+move_table_rook_bishop[x][y][0];
                b = j+move_table_rook_bishop[x][y][1];
                if(a>=0&&a<6&&b>=0&&b<5){
                  if(self_board[a][b])
                    break;
                  if(oppn_board[a][b]){
                    temp = value_list(oppn_board[a][b]);
                    max = temp>max?temp:max;
                    break;
                  }
                }
                else{
                  break;
                }
              }
            }
            my_value+=max;
            break;
          case 6:
            my_value+=900;
            max=0;
            //int a,b,temp,max=0;
            for(int x=0;x<=7;x++){
              a = i+move_table_king[x][0];
              b = j+move_table_king[x][1];
              if(a>=0&&a<6&&b>=0&&b<5){
                if(oppn_board[a][b]){
                  temp = value_list(oppn_board[a][b]);
                  max = temp>max?temp:max;
                }
              }
              else{
                break;
              }
            }
            my_value+=max;
            break;
        }
      }
    }
  }
  for(int i=0; i<BOARD_H; i+=1){ //calculate opponent value
    for(int j=0; j<BOARD_W; j+=1){//value: pawn = 10, rook = 50, bishop = 30, knight = 30
                                        // queen = 90, king = 900
      if((now=oppn_board[i][j])){
        switch(now){
          case 1:
            if(!(1-this->player)){
              if(i==1)
                opponent_value+=90;
              else
                opponent_value+=10;
            }
            else{
              if(i==4)
                opponent_value+=90;
              else  
                opponent_value+=10;
            }
            break;
          case 2:
            opponent_value+=50;
          break;
          case 3:
          case 4:
            opponent_value+=30;
            break;
          case 5:
            opponent_value+=90;
            break;
          case 6:
            opponent_value+=900;
            break;
        }
      }
    }
  }
  return my_value-opponent_value;
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}





/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}