#pragma once
#include "MyString.h"

enum class CellType {
    Integer,
    Fractional,
    String,
    Formula
};

class Cell {
protected:
    MyString data;
    CellType cellType;

    CellType determineType();
public:
    virtual ~Cell() {}
    virtual MyString getValue() const = 0;
    virtual void setValue(const MyString& value) = 0;
    virtual CellType getCellType() const = 0;
    virtual bool isNumeric() const = 0;
};