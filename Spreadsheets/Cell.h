#pragma once
#include "MyString.h"
#include "ConfigEnums.h"

class Cell {
protected:
    MyString data;
    CellType cellType;

    CellType determineType();
public:
    Cell(const MyString& data, CellType type) : data(data), cellType(type) {}

    virtual MyString getValue() const = 0;
    virtual void setValue(const MyString&) = 0;
    virtual CellType getCellType() const = 0;
    virtual bool isNumeric() const = 0;

    virtual ~Cell() = default;
};