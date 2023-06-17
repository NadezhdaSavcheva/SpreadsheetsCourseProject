#include "Table.h"
#include "Utils.h"
#include "CellFactory.h"
#include <sstream>
#include <fstream>
#include <iomanip>

CellType Table::determineType(const MyString& cellValue) {
    if (cellValue.empty()) {
        return CellType::String;
    }
    else if (isString(cellValue)) {
        return CellType::String;
    }
    else if (isInteger(cellValue)) {
        return CellType::Integer;
    }
    else if (isFractional(cellValue)) {
        return CellType::Fractional;
    }
    else {
        return CellType::Formula;
    }
}

void Table::readRowFromFile(std::ifstream& file) {
    MyString line;
    getline(file, line, '\n');
    std::stringstream ss(line.c_str());

    char buff[1024];
    while (ss.getline(buff, 1024, ',')) {
        size_t columnsSize = 0;

        if (buff[0] == '\n') {
            for (size_t i = 0; i < cells[rowsCount].getSize(); i++)
            {
                cells[rowsCount][columnsSize++] = cellFactory(trimString(buff), CellType::String);
            }
        }
        else {
            if (trimString(buff).empty()) {
                cells[rowsCount][columnsSize++] = cellFactory(trimString(buff), CellType::String);
            }
            else {
                cells[rowsCount][columnsSize++] = cellFactory(trimString(buff), determineType(trimString(buff)));
            }
        }

        if (columnsSize > columnsCount)
            columnsCount = columnsSize;

        columnsSize = 0;
    }
    rowsCount++;
}

void Table::loadFromFile(const char* fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return;
    }

    cells.clear();

    while (!file.eof()) {
        readRowFromFile(file);
    }

    file.close();
}

void Table::saveRow(const Vector<Cell*>& row, std::ofstream& ofs) const {
    for (size_t i = 0; i < row.getSize(); i++)
    {
        ofs << row[i]->getValue().c_str();
        if (i != row.getSize() - 1)
            ofs << ",";
    }
    ofs << std::endl;
}

void Table::saveToFile(const char* fileName) const {
    std::ofstream ofs(fileName);
    if (!ofs.is_open())
        return;

    for (size_t i = 0; i < cells.getSize(); i++)
        saveRow(cells[i], ofs);
    ofs.close();
}

void Table::printRow(const Vector<Cell*>& row, const Vector<size_t>& columnWidths) const {
    for (size_t i = 0; i < row.getSize(); i++)
    {
        std::cout << std::left << std::setw(columnWidths[i]) << row[i]->getValue().c_str();
        if (i != row.getSize() - 1)
            std::cout << " | ";
    }
    std::cout << std::endl;
}

void Table::printTable() const {
    Vector<size_t> columnWidths(columnsCount);

    for (size_t i = 0; i < cells.getSize(); i++)
    {
        const Vector<Cell*>& currentRow = cells[i];
        for (size_t j = 0; j < currentRow.getSize(); j++)
        {
            size_t valueLength = currentRow[j]->getValue().length();
            if (valueLength > columnWidths[j])
                columnWidths[j] = valueLength;
        }
    }

    for (size_t i = 0; i < cells.getSize(); i++)
    {
        const Vector <Cell*>& currentRow = cells[i];
        printRow(currentRow, columnWidths);
    }
}

void Table::editCell(int row, int column, const MyString& newValue) {

}

Cell* Table::getCell(int row, int column) const {
    return cells[row - 1][column - 1];
}