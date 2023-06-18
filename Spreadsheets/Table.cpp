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
    char line[1024];
    file.getline(line, 1024, '\n');
    std::stringstream ss(line);

    Vector<Cell*> row;

    char buff[1024];
    while (ss.getline(buff, 1024, ',')) {
        size_t columnsSize = 0;

        if (buff[0] == '\n') {
            for (size_t i = 0; i < row.getCapacity(); i++) {
                row.pushBack(cellFactory(trimString(buff), CellType::String));
                columnsSize++;
            }
        }
        else {
            if (trimString(buff).empty()) {
                row.pushBack(cellFactory(trimString(buff), CellType::String));
                columnsSize++;
            }
            else {
                row.pushBack(cellFactory(trimString(buff), determineType(trimString(buff))));
                columnsSize++;
            }
        }

        if (columnsSize > columnsCount)
            columnsCount = columnsSize;
    }

    cells.pushBack(row);
    rowsCount++;
}

void Table::loadFromFile(const char* fileName) {
    std::ifstream file(fileName, std::ios::_Nocreate);

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
    for (size_t i = 0; i < row.getSize(); i++) {
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

    hasChanges = false;
}

void Table::printRow(const Vector<Cell*>& row, const Vector<size_t>& columnWidths) const {
    for (size_t i = 0; i < row.getSize(); i++) {
        std::cout << std::left << std::setw(columnWidths[i]) << row[i]->getValue().c_str();

        if (i != row.getSize() - 1)
            std::cout << " | ";
    }

    std::cout << std::endl;
}

void Table::printTable() const {
    Vector<size_t> columnWidths(columnsCount);

    for (size_t i = 0; i < cells.getSize(); i++) {
        const Vector<Cell*>& currentRow = cells[i];

        for (size_t j = 0; j < currentRow.getSize(); j++) {
            size_t valueLength = currentRow[j]->getValue().length();

            if (valueLength > columnWidths[j])
                columnWidths[j] = valueLength;
        }
    }

    for (size_t i = 0; i < cells.getSize(); i++) {
        const Vector <Cell*>& currentRow = cells[i];
        printRow(currentRow, columnWidths);
    }
}

void Table::editCell(size_t row, size_t column, const MyString& newValue) {
    getCell(row, column)->setValue(trimString(newValue));
    hasChanges = true;
}

Cell* Table::getCell(size_t row, size_t column) const {
    if (row >= rowsCount || column >= columnsCount)
        throw;

    return cells[row - 1][column - 1];
}

bool Table::getChangesFlag() const {
    return hasChanges;
}

void Table::setFileName(const MyString& name) {
    fileName = name;
}

MyString Table::getFileName() const {
    return fileName;
}