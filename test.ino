#include "joystick.h"
#include <Arduino.h>
#include "Matrix8x8.h"
#include "cursor.h"
#include "LedButtun.h"
#include "TouchSensor.h"
#include "Board.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <iostream>
#ifndef PSTR
 #define PSTR 
#endif


Matrix8x8 Matrix1;
Cursor Cursor1(Matrix1, 0);
LedButtun ledButtun1;
joystick Joystick1;
TouchSensor TouchSensor1;
Board Board1(Matrix1, 0, Cursor1);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, D6,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

 //Tableau possedant plusieurs couleurs en son sein
 const uint16_t colors[] = {
  matrix.Color(255, 0, 0),   // Rouge
  matrix.Color(255, 127, 0), // Orange
  matrix.Color(255, 255, 0), // Jaune
  matrix.Color(0, 255, 0),   // Vert
  matrix.Color(0, 0, 255),   // Bleu
  matrix.Color(75, 0, 130),  // Indigo
  matrix.Color(148, 0, 211)  // Violet
};

//variables utilisées pour gérer l'affichage du texte
int x    = matrix.width();
int pass = 0;
int GameBegin =0;
bool GameResetInProgress = false;


void setup() {
  pinMode(D8, INPUT);
  pinMode(D3, OUTPUT);
  pinMode(D6, OUTPUT);
  digitalWrite(D3, HIGH); 
  matrix.begin();
  matrix.setBrightness(10);
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(255, 0, 0));
  Serial.begin(9600);
}






void loop() {

  //lance le jeu dès lors qu'on touche le capteur en passant la variable Gamebegin à 1
  if (TouchSensor1.readValue()==1 and !GameBegin){
    matrix.fillScreen(0);
    Board1.reset();
    Matrix1.reset();
    GameBegin=1;
}
    //Permet de faire défiler un message tant que la partie n'a pas été lancée
    if(!GameBegin){
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("Please touch the sensor to start the game"));
    if (--x < -240) {
      x = matrix.width();
      if (++pass >= 7) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(100);
    }
 
  //On effectue cette boucle while tant que la partie n'est pas finie
  while (!Board1.GameState and GameBegin) {

 if (Joystick1.directionJoy() == 1) {
      Cursor1.moveRight();
    }
    if (Joystick1.directionJoy() == 2) {
      Cursor1.moveLeft();
    }
    //si le bouton est pressé, alors on joue dans la colonne actuelle
    if (ledButtun1.readValue() == 0) {
      Board1.PlayMove();
     std :: cout << Board1.Mat; // utilise la redefinition de << pour afficher la matrice de jeu
     Serial.println("");
      for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
          // Vérifie si la valeur dans la case est égale à 1, ie que le jeton appartient au joueur 1
          if (Board1.Mat.getValue(row, col) == 1) {
            // Allume la case correspondante sur la matrice, en rouge
            matrix.drawPixel(col, row, matrix.Color(255, 0, 0));
            matrix.show();
            delay(200); 
          }
          // Vérifie si la valeur dans la case est égale à 2, ie que le jeton appartient au joueur 2
          if (Board1.Mat.getValue(row, col) == 2) {
            // Allume la case correspondante sur la matrice, en jaune
            matrix.drawPixel(col, row, matrix.Color(255, 255, 0));
            matrix.show();
            delay(200);  
          }
        }
      }
    }
     Board1.GameResult(); 

    //fais clignotter une LED de la couleur du joueur 1 sur la premiere ligne, pour indiquer au joueur où se situe le curseur. 
    if (Board1.player == 1) {
      matrix.drawPixel(Cursor1.getColumn(), 0, matrix.Color(255, 0, 0));
      matrix.show();
      delay(100);

      matrix.drawPixel(Cursor1.getColumn(), 0, matrix.Color(0, 0, 0));
      matrix.show();
      delay(100);
    }
    
    //meme chose pour le joueur 2
    if (Board1.player == 2) {
      matrix.drawPixel(Cursor1.getColumn(), 0, matrix.Color(255, 255, 0));
      matrix.show();
      delay(100);

      matrix.drawPixel(Cursor1.getColumn(), 0, matrix.Color(0, 0, 0));
      matrix.show();
      delay(100);
    }
  }

  //affiche un message de victoire en boucle si le joueur 1 a gagné. Le message change de couleur après chaque affichage.
  if (Board1.player == 1 and GameBegin) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("Game is over, player 1 is just too good bro"));
    if (--x < -260) {
      x = matrix.width();
      if (++pass >= 7) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(100);
  }

  ////affiche un message de victoire en boucle si le joueur 2 a gagné. Le message change de couleur après chaque affichage.
  if (Board1.player == 2 and GameBegin) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("Game is over, player 2 is just too good bro"));
    if (--x < -260) {
      x = matrix.width();
      if (++pass >= 7) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(100);
  }
}

 









