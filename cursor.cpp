#include "Matrix8x8.h"
#include "Cursor.h"
#include <stdexcept>
#include <Arduino.h>

Cursor::Cursor(Matrix8x8 matrix, int initialColumn) : Matrixx(matrix), column(initialColumn) {}
Cursor::Cursor() : Matrixx(), column(0) {}

void Cursor::moveLeft() {
    try {
        if (column > 0) {
            --column;
        } else {
            throw std::out_of_range("Cursor is at the leftmost column");  // lance une exception si on essaye d'aller à gauche alors que le curseur se situe sur la colonne la plus à gauche
        }
    } catch (const std::out_of_range &e) {  
       Serial.println("Exception caught: " + String(e.what())); // Affiche le message d'exception sur le moniteur série  
       column = 7;   // Gére l'exception : ici, le curseur passe de l'autre coté
    }
}

void Cursor::moveRight() {
    try {
        const int maxColumn = 7;
        if (column < maxColumn) {
            ++column;
        } else {
            throw std::out_of_range("Cursor is at the rightmost column");   // lance une exception si on essaye d'aller à droite alors que le curseur se situe sur la colonne la plus à droite
        }
    } catch (const std::out_of_range &e) {
       Serial.println("Exception caught: " + String(e.what()));   // Affiche le message d'exception sur le moniteur série
        column = 0;   // Gérer l'exception : ici, le curseur passe de l'autre coté
    }
}

int Cursor::getColumn() const {
    return column;
}



