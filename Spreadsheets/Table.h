#pragma once
#include "Cell.h"
#include "Vector.hpp"

class Table {
private:
    Vector<Vector<Cell*>> cells;
public:
    Table();
    ~Table();
    void loadFromFile(const MyString& filename);
    void saveToFile(const string& filename) const;
    void printTable() const;
    void editCell(int row, int column, const MyString& newValue);
    Cell* getCell(int row, int column) const;
};