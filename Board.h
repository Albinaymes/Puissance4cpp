#ifndef BOARD_H
#define BOARD_H

#include "Matrix8x8.h" 
#include "Cursor.h"


class Board  {
public:
     Board(Matrix8x8& matrix, int initialColumn, Cursor& curseur);
     Board();
    ~Board(); 
    void PlayMove();
    void GameResult();// cette fonction change en fonction du resultat de la partie en cours, ou non, la valeur de GameState
    void reset();
    Matrix8x8 Mat;
    int GameState ;  //0 si la partie est toujours en cours, 1 si il y a un gagnant
    int player ; // 1 quand c'est au player 1 de jouer, 2 quand c'est au player 2
    
    
private :
      Cursor& Curs;
    
    };

#endif 