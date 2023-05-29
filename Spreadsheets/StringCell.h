#pragma once
#include "Cell.h"

class StringCell : public Cell {
private:
    MyString value;

    bool isValidString() const;
public:
    MyString getValue() const override;
    void setValue(const MyString& value) override;
    CellType getCellType() const override;
    bool isNumeric() const override;
};