#pragma once
#include "Cell.h"
#include "Vector.hpp"

class Table {
private:
    Vector<Vector<Cell*>> cells;
    MyString fileName;
    size_t rowsCount = 0;
    size_t columnsCount = 0;
    bool mutable hasChanges = false;

    CellType determineType(const MyString& cellValue);
    void readRowFromFile(std::ifstream& file);
    void printRow(const Vector<Cell*>& row, const Vector<size_t>& columnWidths) const;
    void saveRow(const Vector<Cell*>& row, std::ofstream& ofs) const;
public:
    void loadFromFile(const char* fileName);
    void saveToFile(const char* fileName) const;
    void printTable() const;
    void editCell(size_t row, size_t column, const MyString& newValue);
    Cell* getCell(size_t row, size_t column) const;
    bool getChangesFlag() const;
    void setFileName(const MyString& name);
    MyString getFileName() const;
};