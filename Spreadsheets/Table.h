#pragma once
#include "Cell.h"
#include "Vector.hpp"

class Table {
private:
    Vector<Vector<Cell*>> cells;
    size_t rowsCount = 0;
    size_t columnsCount = 0;

    CellType determineType(const MyString& cellValue);
    void readRowFromFile(std::ifstream& file);
    void printRow(const Vector<Cell*>& row, const Vector<size_t>& columnWidths) const;
    void saveRow(const Vector<Cell*>& row, std::ofstream& ofs) const;
public:
    void loadFromFile(const char* fileName);
    void saveToFile(const char* fileName) const;
    void printTable() const;
    void editCell(int row, int column, const MyString& newValue);
    Cell* getCell(int row, int column) const;
};