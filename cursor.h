
#ifndef CURSOR_H
#define CURSOR_H

#include "Matrix8x8.h"  

class Cursor {
public:
    Cursor(Matrix8x8 matrix, int initialColumn);
    Cursor();
    void moveLeft();
    void moveRight();
    int getColumn() const;

private:
    Matrix8x8 Matrixx;
    int column;
};

#endif 

