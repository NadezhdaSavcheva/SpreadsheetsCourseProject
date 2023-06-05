#pragma once
#include "Cell.h"

class StringCell : public Cell {
public:
    StringCell(const MyString& data) : Cell(data, CellType::String) {}
    bool isValidString(const MyString& data) const;
    MyString getValue() const override;
    void setValue(const MyString& data) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};