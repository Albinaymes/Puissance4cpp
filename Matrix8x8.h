#ifndef MATRIX8X8_H
#define MATRIX8X8_H
#include <ostream>
#include <vector> 

class Matrix8x8 {
public:
    Matrix8x8();
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);
    int insertToken(int column, int player);
    void reset();
   friend std::ostream& operator<<(std::ostream& os, const Matrix8x8& matrix);
    
private:
    int rows;
    int columns;
    std::vector<std::vector<int>> matrix;
};

#endif 

