#include "Matrix8x8.h"
#include "Board.h"
#include "Cursor.h"
#include <Arduino.h>
#include <stdexcept>

Cursor emptyC;
Board::Board() : player(1), Mat(), GameState(0), Curs(emptyC) {}
Board::Board(Matrix8x8& matrix, int initialColumn, Cursor& Curseur): player(1), Mat(matrix), GameState(0), Curs(Curseur) {}
Board::~Board() {}

void Board::PlayMove() {
    //On obtient la colonne à partir de la position du curseur
    int col = Curs.getColumn();

    try {
        // On Essaye d'insérer le jeton du joueur dans la colonne choisie
        if (!Mat.insertToken(col, player)) {
            throw std::runtime_error("Token insertion failed");  // Jette une exception si l'insertion échoue
        }
        // On met à jour le joueur (la fonction insertToken change le joueur peu importe si l'insertion a réussie, donc on compense ici en cas d'echec)
        player = (player == 1) ? 2 : 1;
       
    } catch (const std::exception& e) {
      Serial.println(e.what()); // On écrit le message d'exception sur le moniteur serie si l'insertion du jeton a échouée

    }
}

void Board::GameResult() {
    // Vérifie les lignes horizontales
    /*Pour ce faire, on va venir boucler sur chacune des lignes. Sur chaque ligne, on va boucler 5 fois. On va venir regarder si les valeurs des colonnes 0 à 4
    sont identique, et differentes de zero. Si ce n'est pas le cas, on decale et on compare les valeurs  des colonnes 1 à 5. Et ainsi de suite pour faire
    toute la ligne. Et ceci sur les 8 lignes.
    */
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col <= 4; ++col) {
            int val = Mat.getValue(row, col);
            if (val != 0 && Mat.getValue(row, col + 1) == val && Mat.getValue(row, col + 2) == val && Mat.getValue(row, col + 3) == val) {
                // Il y a un gagnant
                player = (player == 1) ? 2 : 1;//la fonction insert token change le player direct après, donc sans cette ligne ce n'est pas le bon joueur qui est affiché
                GameState = 1;
                return;
            }
        }
    }

    // Vérifie les lignes verticales
    // Meme logique que precedemment
    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row <= 4; ++row) {
            int val = Mat.getValue(row, col);
            if (val != 0 && Mat.getValue(row + 1, col) == val && Mat.getValue(row + 2, col) == val && Mat.getValue(row + 3, col) == val) {
                // Il y a un gagnant
                player = (player == 1) ? 2 : 1;
                GameState = 1;
                return;
            }
        }
    }

    // Vérifie les diagonales (de gauche à droite)
    /*Pour ce faire, on va venir boucler sur les lignes 0 à 4. Sur chaque ligne, on va boucler 5 fois. On va venir regarder si les valeurs des cases (col, ligne)
    , (col+1, ligne+1), (col+2, ligne+2), (col+3, ligne+3) sont identiques, c'est à dire la diagonale. Si ce n'est pas le cas, on teste la diagonale d'à coté. Et ce 5 
    fois pour tester toutes les combinaisons diagonales possibles partantes de la ligne 0. On repete le processus sur les 4 lignes suivantes, et on aura ainsi tester
    toutes les combinaisons diagonales (de gauche à droite) possibles. 
    */
    for (int row = 0; row <= 4; ++row) {
        for (int col = 0; col <= 4; ++col) {
            int val = Mat.getValue(row, col);
            if (val != 0 && Mat.getValue(row + 1, col + 1) == val && Mat.getValue(row + 2, col + 2) == val && Mat.getValue(row + 3, col + 3) == val) {
                // Il y a un gagnant
                player = (player == 1) ? 2 : 1;
                GameState = 1;
                return;
            }
        }
    }

    // Vérifie les diagonales (de droite à gauche)
    // meme logique que precedemment mais dans l'autre sens
    for (int row = 0; row <= 4; ++row) {
        for (int col = 3; col < 8; ++col) {
            int val = Mat.getValue(row, col);
            if (val != 0 && Mat.getValue(row + 1, col - 1) == val && Mat.getValue(row + 2, col - 2) == val && Mat.getValue(row + 3, col - 3) == val) {
                // Il y a un gagnant
                player = (player == 1) ? 2 : 1;
                GameState = 1;
                return;
            }
        }
    }

}

void Board::reset() {
    // Réinitialise les membres de la classe Board
    player = 1;
    GameState = 0;
    Mat.reset();
}


