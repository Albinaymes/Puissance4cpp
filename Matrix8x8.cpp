#include "Matrix8x8.h"
#include <ostream>

Matrix8x8::Matrix8x8() : rows(8), columns(8), matrix(rows, std::vector<int>(columns, 0)) {}

// Redefinition de l'operateur << pour pouvoir afficher la matrice sur le moniteur série après chaque tour
std::ostream& operator<<(std::ostream& os, const Matrix8x8& matrix) {
    for (int row = 0; row < matrix.rows; ++row) {
        for (int col = 0; col < matrix.columns; ++col) {
            os << matrix.matrix[row][col] << ' ';
        }
        os << '\n';
    }
    return os;
}

int Matrix8x8::getValue(int row, int col) const {
    return matrix[row][col];
}

void Matrix8x8::setValue(int row, int col, int value) {
    matrix[row][col] = value;
}

//Fonction permettant l'insertion d'un jeton, renvoie 1 si l'insertion s'est bien passé, 0 sinon
int Matrix8x8::insertToken(int column, int player) {
    int ret =0;
    // cherche la première case vide (où la valeur est 0) dans la colonne
    for (int row = rows - 1; row >= 0; --row) {
        if (matrix[row][column] == 0) {
            // Place le jeton du joueur dans la case vide
            matrix[row][column] = player;
            ret =1;
            break; // Quitte la boucle après avoir placé le jeton
        }
    }
    return ret;
}

void Matrix8x8::reset() {
    // Réinitialise toutes les valeurs de la matrice à zéro
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            matrix[row][col] = 0;
        }
    }
}



