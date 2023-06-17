#pragma once
#include "Utils.h"
#include "Vector.hpp"
#include "MyString.h"
#include <fstream>
#include <sstream>
#include <iomanip>

struct Value
{
     MyString str;
};

struct Row
{
    Vector<Value> values;
};

struct CsvFile
{
    size_t rowsCount = 0;
    size_t columnsCount = 0;
    Vector<Row> rows;
};

Row readRow(std::ifstream& ifs)
{
    MyString line;
    getline(ifs, line, '\n');
    std::stringstream ss(line.c_str());

    Row currentRow;
    MyString value;
    while (getline(ss, value, ','))
    {
        Value currentValue;
        trimString(value);
        currentValue.str = value;
        currentRow.values.pushBack(currentValue);
    }
    return currentRow;
}

CsvFile parseFromFile(const char* fileName)
{
    std::ifstream input(fileName);
    if (!input.is_open())
        throw std::exception("Error");

    CsvFile resultFile;
    MyString line;

    // Read the first line to determine the number of columns
    if (getline(input, line, '\n'))
    {
        std::stringstream ss(line.c_str());
        MyString value;
        while (getline(ss, value, ','))
        {
            Value currentValue;
            trimString(value);
            currentValue.str = value;
            resultFile.columnsCount++;
        }
    }

    // Reset the file pointer to the beginning
    input.clear();
    input.seekg(0, std::ios::beg);

    // Read the remaining lines to determine the number of rows
    while (getline(input, line, '\n'))
    {
        /*Row currentRow;
        std::stringstream ss(line.c_str());
        MyString value;
        while (getline(ss, value, ','))
        {
            Value currentValue;
            trimString(value);
            currentValue.str = value;
            currentRow.values.pushBack(currentValue);
        }*/
        resultFile.rows.pushBack(readRow(input));
        resultFile.rowsCount++;
    }

    input.close();
    return resultFile;
}

void printRow(const Row& row, const Vector<size_t>& columnWidths)
{
    for (size_t i = 0; i < row.values.getSize(); i++)
    {
        std::cout << std::left << std::setw(columnWidths[i]) << row.values[i].str;
        if (i != row.values.getSize() - 1)
            std::cout << " | ";
    }
    std::cout << std::endl;
}

void print(const CsvFile& fileToPrint)
{
    Vector<size_t> columnWidths(fileToPrint.columnsCount);

    for (size_t i = 0; i < fileToPrint.rows.getSize(); i++)
    {
        const Row& currentRow = fileToPrint.rows[i];
        for (size_t j = 0; j < currentRow.values.getSize(); j++)
        {
            size_t valueLength = currentRow.values[j].str.length();
            if (valueLength > columnWidths[j])
                columnWidths[j] = valueLength;
        }
    }

    for (size_t i = 0; i < fileToPrint.rows.getSize(); i++)
    {
        const Row& currentRow = fileToPrint.rows[i];
        printRow(currentRow, columnWidths);
    }
}

void saveCsvRow(const Row& row, std::ofstream& ofs)
{
    for (size_t i = 0; i < row.values.getSize(); i++)
    {
        ofs << row.values[i].str;
        if (i != row.values.getSize() - 1)
            ofs << ",";
    }
    ofs << std::endl;
}

void saveCsvToFile(const CsvFile& file, const char* fileName)
{
    std::ofstream ofs(fileName);
    if (!ofs.is_open())
        return;

    for (size_t i = 0; i < file.rows.getSize(); i++)
        saveCsvRow(file.rows[i], ofs);
    ofs.close();
}

/*#include "Vector.hpp"
#include "MyString.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iomanip>

struct Value
{
    MyString str;
};

struct Row
{
    Vector<Value> values;
};

struct CsvFile
{
    size_t rowsCount = 0;
    size_t columnsCount = 0;
    Vector<Row> rows;
};

Row readRow(std::ifstream& ifs)
{
    MyString line;
    getline(ifs, line, '\n');
    std::stringstream ss(line.c_str());

    Row currentRow;
    MyString value;
    while (getline(ss, value, ','))
    {
        Value currentValue;
        trimString(value);
        currentValue.str = value;
        currentRow.values.pushBack(currentValue);
    }
    return currentRow;
}

CsvFile parseFromFile(const char* fileName)
{
    std::ifstream input(fileName);
    if (!input.is_open())
        throw std::exception("Error");

    CsvFile resultFile;

    while (!input.eof())
        resultFile.rows.pushBack(readRow(input));

    input.close();
    return resultFile;
}

void printRow(const Row& row)
{
    for (size_t i = 0; i < row.values.getSize(); i++)
        std::cout << std::left << std::setw(20) << row.values[i].str;
    std::cout << std::endl;
}

void print(const CsvFile& fileToPrint)
{
    for (size_t i = 0; i < fileToPrint.rows.getSize(); i++)
        printRow(fileToPrint.rows[i]);
}

void saveCsvRow(const Row& row, std::ofstream& ofs)
{
    for (size_t i = 0; i < row.values.getSize(); i++)
    {
        ofs << row.values[i].str;
        if (i != row.values.getSize() - 1)
            ofs << ",";
    }
    ofs << std::endl;
}

void saveCsvToFile(const CsvFile& file, const char* fileName)
{
    std::ofstream ofs(fileName);
    if (!ofs.is_open())
        return;

    for (size_t i = 0; i < file.rows.getSize(); i++)
        saveCsvRow(file.rows[i], ofs);
    ofs.close();
}*/

//int getColumnIndex(const CsvFile& csvFile, const MyString& columnName)
//{
//    for (size_t i = 0; i < csvFile.columnsNames.values.getSize(); i++)
//    {
//        if (csvFile.columnsNames.values[i].str == columnName)
//            return static_cast<int>(i);
//    }
//    return -1;
//}

//bool changeValue(CsvFile& csvFile, size_t row, size_t column, const MyString& changeWith)
//{
//    if (columnIndex == -1)
//        return false;
//    for (size_t i = 0; i < csvFile.rows.getSize(); i++)
//    {
//        if (strcmp(csvFile.rows[i].values[columnIndex].str.c_str(), valueToChange.c_str()) == 0)
//        {
//            csvFile.rows[i].values[columnIndex].str = changeWith;
//            return true;
//        }
//    }
//    return false;
//}